//
//  TacoMonitor.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/14/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "TacoMonitor.h"

#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <python3.5/Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <wiringPi.h>

#include "OBDIIController.h"


// we want a signal pin that is HIGH on boot, so the buzzer does not sound.
// https://raspberrypi.stackexchange.com/questions/51479/gpio-pin-states-on-powerup?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
//	"The power on state is defined in BCM2835 ARM Peripherals page 102.
//
//	Basically all GPIO pins are in INPUT mode, GPIO 0-8 have pull-ups to 3V3 enabled, GPIO 9-27 have pull-downs to 0V enabled."

#define BUZZER_BCM_PIN		6

#define BUZZER_PERIOD		1000


using namespace std;
using namespace tacomon;

/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

static void SetupPython();
static void ExecPython(string python);
static void TerminatePython();
static unsigned LightLevel();
static void DisplayString(string str);
static void DisplaySmallString(unsigned display, string str);
static void FillDisplay(bool fill);
static void SetupGPIO();

/**************************************************************************************
     Lifecycle
 **************************************************************************************/

TacoMonitor::TacoMonitor():
	m_obdiiController(make_shared<OBDIIController>()),
	m_stop(false) {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

int TacoMonitor::start(const vector<string>& args) {
	
	SetupPython();
	SetupGPIO();
	
	if (!m_obdiiController->connect()) {
		cout << "Couldn't create OBD-II serial connection.";
	}

	while (!m_stop) {
		update();
		
//		bool b1 = false, b2 = false, b3 = false, b4 = false, b5 = false;
//		PollButtons(b1, b2, b3, b4, b5);
//		
//		if (b1) cout << "b1" << endl;
//		if (b2) cout << "b2" << endl;
//		if (b3) cout << "b3" << endl;
//		if (b4) cout << "b4" << endl;
//		if (b5) cout << "b5" << endl;
	}
	
	shutdown();
}

void TacoMonitor::stop() {
	cout << "TacoMonitor::stop()" << endl;
	
	m_stop = true;
}

/**************************************************************************************
     Private
 **************************************************************************************/

void TacoMonitor::update() {
	
	auto lux = LightLevel();
	cout << "lux: " << lux << endl;
	
	FillDisplay(true);
	
	digitalWrite(BUZZER_BCM_PIN, LOW); // low == on
	delay(BUZZER_PERIOD/2);
	
	DisplayString("DICKS");
	
	digitalWrite(BUZZER_BCM_PIN, HIGH);
	delay(BUZZER_PERIOD/2);
}

void TacoMonitor::shutdown() {
	cout << "TacoMonitor::shutdown()" << endl;
	
	digitalWrite(BUZZER_BCM_PIN, HIGH);
	
	DisplayString("");
	
	TerminatePython();
	
	m_obdiiController->disconnect();
}

/**************************************************************************************
     Static
 **************************************************************************************/

void SetupPython() {
	
	Py_SetProgramName(L"taco_mon_python");  /* optional but recommended */
	Py_Initialize();
	PyRun_SimpleString("import smbus\n"
					   "from time import sleep\n"
					   "from microdotphat import clear, set_brightness, show, write_string, draw_tiny, fill, WIDTH, HEIGHT\n");
}

void ExecPython(string python) {
	
	PyRun_SimpleString(python.c_str());
}

void TerminatePython() {
	
	Py_Finalize();
}

unsigned LightLevel() {
	// This code is designed to work with the TSL2561_I2CS I2C Mini Module available from ControlEverything.com.
	// https://www.controleverything.com/content/Light?sku=TSL2561_I2CS#tabs-0-product_tabset-2
	
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-0";
	if ((file = open(bus, O_RDWR)) < 0)  {
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, TSL2561 I2C address is 0x39(57)
	ioctl(file, I2C_SLAVE, 0x39);
	
	// Select control register(0x00 | 0x80)
	// Power ON mode(0x03)
	char config[2] = {0};
	config[0] = 0x00 | 0x80;
	config[1] = 0x03;
	write(file, config, 2);
	// Select timing register(0x01 | 0x80)
	// Nominal integration time = 402ms(0x02)
	config[0] = 0x01 | 0x80;
	config[1] = 0x02;
	write(file, config, 2);
	//sleep(1);
	
	// Read 4 bytes of data from register(0x0C | 0x80)
	// ch0 lsb, ch0 msb, ch1 lsb, ch1 msb
	char reg[1] = {0x0C | 0x80};
	write(file, reg, 1);
	char data[4] = {0};
	if (read(file, data, 4) != 4) {
		printf("Erorr : Input/output Erorr \n");
	}
	else {
		// Convert the data
		float ch0 = (data[1] * 256 + data[0]);
		float ch1 = (data[3] * 256 + data[2]);
		
		// Output data to screen
//		printf("Full Spectrum(IR + Visible) : %.2f lux \n", ch0);
//		printf("Infrared Value : %.2f lux \n", ch1);
//		printf("Visible Value : %.2f lux \n", (ch0 - ch1));
		return ch0 - ch1;
	}
	
	return 0;
}

void DisplayString(string str) {
	
	char execStr[1024];
	sprintf(execStr, "clear()\n" \
			"write_string(\"%s\", kerning=False)\n" \
			"show()\n", str.c_str());
	ExecPython(execStr);
}

void DisplaySmallString(unsigned display, string str) {
	
	char execStr[1024];
	sprintf(execStr, "clear()\n" \
			"draw_tiny(%d, \"%s\")\n" \
			"show()\n", display, str.c_str());
	ExecPython(execStr);
}

void FillDisplay(bool fill) {
	
	char execStr[1024];
	sprintf(execStr, "clear()\n" \
			"fill(%s)\n" \
			"show()\n", (fill ? "1" : "0"));
	ExecPython(execStr);
}

void SetupGPIO() {
	
	wiringPiSetupGpio(); // use BCM pin numbers
	// http://wiringpi.com/reference/
	pinMode(BUZZER_BCM_PIN, OUTPUT);
	digitalWrite(BUZZER_BCM_PIN, HIGH); // high == off
	
//	pinMode(BUTTON_1_PIN, INPUT);
//	pinMode(BUTTON_2_PIN, INPUT);
//	pinMode(BUTTON_3_PIN, INPUT);
//	pinMode(BUTTON_4_PIN, INPUT);
//	pinMode(BUTTON_5_PIN, INPUT);
}

