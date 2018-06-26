//
//  SensorHub.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "SensorHub.h"

#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "smbus.h"


using namespace std;
using namespace tacomon;


/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

static unsigned AmbientLight();
static float AmbientTemperature();
static void Sleep(unsigned milliseconds);

/**************************************************************************************
     Lifecycle
 **************************************************************************************/

SensorHub::SensorHub():
	m_stop(nullptr),
	m_ambientLight(0),
	m_ambientTemperature(0) {
	
		m_updateThread = thread(&SensorHub::updateLoop, this);
}

SensorHub::~SensorHub() {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

unsigned SensorHub::ambientLight() {
	lock_guard<mutex> guard(m_mtx);
	
	return m_ambientLight;
}

float SensorHub::ambientTemperature() {
	lock_guard<mutex> guard(m_mtx);
	
	return m_ambientTemperature;
}

void SensorHub::shutdown() {
	
	m_mtx.lock();
	m_stop = true;
	m_mtx.unlock();
	cout << "Waiting for sensor poll loop to complete..." << endl;
	m_updateThread.join();
}

/**************************************************************************************
     Private
 **************************************************************************************/

void SensorHub::updateLoop() {
	
	while (m_mtx.lock(), !m_stop) {
		m_mtx.unlock();
		
		auto lux = AmbientLight();
		m_mtx.lock();
		m_ambientLight = lux;
		m_mtx.unlock();
		
		auto celsius = AmbientTemperature();
		m_mtx.lock();
		m_ambientTemperature = celsius;
		m_mtx.unlock();
		
		Sleep(25);
	}
}                  

/**************************************************************************************
     Static
 **************************************************************************************/

unsigned AmbientLight() {
	
	static const char *BUS_LOCATION = (char *)"/dev/i2c-0";
	static const unsigned char I2C_ADDR = 0x39;
	
	// This code is designed to work with the TSL2561_I2CS I2C Mini Module available from ControlEverything.com.
	// https://www.controleverything.com/content/Light?sku=TSL2561_I2CS#tabs-0-product_tabset-2
	
	// Create I2C bus
	static int fd = -1;
	if (fd == -1) {
		//static const char *bus = (char *)"/dev/i2c-0";
		if ((fd = open(BUS_LOCATION, O_RDWR)) < 0)  {
			printf("Failed to open TSL2561 I2C bus.\n");
			exit(1);
		}
		// get I2C device, TSL2561 I2C address is 0x39(57)
		if (ioctl(fd, I2C_SLAVE, I2C_ADDR) < 0) {
			printf("Failed to get TSL2561 I2C device port.\n");			
			close(fd);
			exit(1);
		}
		
		// Select control register(0x00 | 0x80)
		// Power ON mode(0x03)
		char config[2] = {0};
		config[0] = 0x00 | 0x80;
		config[1] = 0x03;
		write(fd, config, 2);
		// Select timing register(0x01 | 0x80)
		// Nominal integration time = 402ms(0x02)
		config[0] = 0x01 | 0x80;
		config[1] = 0x02;
		write(fd, config, 2);
		//sleep(1);
	}
	
	// Read 4 bytes of data from register(0x0C | 0x80)
	// ch0 lsb, ch0 msb, ch1 lsb, ch1 msb
	unsigned char reg[1] = {0x0C | 0x80};
	write(fd, reg, 1);
	char data[4] = {0};
	if (read(fd, data, 4) != 4) {
		printf("TSL2561 I2C input/output error.\n");
	}
	else {
		float full = (data[1] * 256 + data[0]);
		float inf = (data[3] * 256 + data[2]);
		float vis = full - inf;
		
		return vis;
	}
	
	return 0;
}

float AmbientTemperature() {
	
	static const char *BUS_LOCATION = "/dev/i2c-0";
	static const unsigned char I2C_ADDR = 0x77;
	
//	static short int ac1;
//	static short int ac2; 
//	static short int ac3; 
//	static unsigned short int ac4;
//	static unsigned short int ac5; // +
//	static unsigned short int ac6; // +
//	static short int b1; 
//	static short int b2;
//	static short int mb;
//	static short int mc;
//	static short int md; // +
	
	struct Utils {
		
		static int ReadInt(int fd, unsigned char address) {
			int res = i2c_smbus_read_word_data(fd, address);
			if (res < 0) {
				cout << "Chouldn't read data from BMP085." << endl;
				close(fd);
				exit(1);
			}
			
			// convert result to 16 bits and swap bytes
			res = ((res<<8) & 0xFF00) | ((res>>8) & 0xFF);
			
			return res;
		}
		
		static void WriteByte(int fd, unsigned char address, unsigned char value) {
			if (i2c_smbus_write_byte_data(fd, address, value) < 0) {
				cout << "Chouldn't write data to BMP085." << endl;
				close(fd);
				exit(1);
			}
		}
		
		static unsigned int ReadUncalibratedTemp(int fd) {
			unsigned int ut = 0;
			
			// Write 0x2E into Register 0xF4
			// This requests a temperature reading
			WriteByte(fd, 0xF4, 0x2E);
			
			// Wait at least 4.5ms
			Sleep(5);
			
			// Read the two byte result from address 0xF6
			return ReadInt(fd, 0xF6);
		}
		
		static float ReadTemperature(unsigned int ut,
									 unsigned short int ac5, unsigned short int ac6,
									 short int mc, short int md) {
			int x1, x2;
			
			x1 = (((int)ut - (int)ac6)*(int)ac5) >> 15;
			x2 = ((int)mc << 11)/(x1 + md);
			//b5 = x1 + x2;
			
			//unsigned int result = ((b5 + 8)>>4);
			return (double)(((x1 + x2 + 8) >> 4)) / 10.0;
		}
	};
	
	static int fd = -1;
	if (fd == -1) {

		// open port for reading and writing
		if ((fd = open(BUS_LOCATION, O_RDWR)) < 0) {
			printf("Failed to open BMP085 I2C bus.\n");
			exit(1);
		}
		
		// set port options and set the address of the device
		if (ioctl(fd, I2C_SLAVE, I2C_ADDR) < 0) {		
			printf("Failed to get BMP085 I2C device port.\n");			
			close(fd);
			exit(1);
		}
	}
	
	// read calibration values -- not clear if these change.
	short int ac1 = Utils::ReadInt(fd, 0xAA);
	short int ac2 = Utils::ReadInt(fd, 0xAC);
	short int ac3 = Utils::ReadInt(fd, 0xAE);
	unsigned short int ac4 = Utils::ReadInt(fd, 0xB0);
	unsigned short int ac5 = Utils::ReadInt(fd, 0xB2);
	unsigned short int ac6 = Utils::ReadInt(fd, 0xB4);
	short int b1 = Utils::ReadInt(fd, 0xB6);
	short int b2 = Utils::ReadInt(fd, 0xB8);
	short int mb = Utils::ReadInt(fd, 0xBA);
	short int mc = Utils::ReadInt(fd, 0xBC);
	short int md = Utils::ReadInt(fd, 0xBE);

	return Utils::ReadTemperature(Utils::ReadUncalibratedTemp(fd), ac5, ac6, mc, md);
}

void Sleep(unsigned milliseconds) {
	
	usleep(milliseconds * 1000);
}
