//
//  InputManager.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "InputManager.h"

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

static InputManager::BUTTON ButtonShimDown();
static void Sleep(unsigned milliseconds);

/**************************************************************************************
     Lifecycle
 **************************************************************************************/

InputManager::InputManager():
	m_stop(false),
	m_buttonsDown(set<BUTTON>()),
	m_buttonsPressed(set<BUTTON>()),
	m_buttonsPressedCleared(set<BUTTON>()) {
	
		m_updateThread = thread(&InputManager::updateLoop, this);
}

InputManager::~InputManager() {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

bool InputManager::buttonDown(BUTTON button) {
	
	return m_buttonsDown.count(button);
}

bool InputManager::buttonPressed(BUTTON button) {
	
	bool pressed = m_buttonsPressed.count(button);
	if (pressed) {
		m_buttonsPressed.erase(button);
		m_buttonsPressedCleared.insert(button);
	}
	return pressed;
}

set<InputManager::BUTTON> InputManager::buttonsDown() {
	
	auto buttonsDownCopy = m_buttonsDown;
	return buttonsDownCopy;
}

set<InputManager::BUTTON> InputManager::buttonsPressed() {
	
	auto buttonsPressedCopy = m_buttonsPressed;
	m_buttonsPressed.clear();
	return buttonsPressedCopy;
}

void InputManager::shutdown() {
	
	m_mtx.lock();
	m_stop = true;
	m_mtx.unlock();
	cout << "Waiting for button poll loop to complete..." << endl;
	m_updateThread.join();
}

/**************************************************************************************
     Private
 **************************************************************************************/

void InputManager::updateLoop() {
	
	while (m_mtx.lock(), !m_stop) {
		m_mtx.unlock();
		
		auto down = ButtonShimDown();
		auto downRaw = static_cast<underlying_type<BUTTON>::type>(down);
		
		static BUTTON buttons[] = {
			InputManager::BUTTON::A,
			InputManager::BUTTON::B,
			InputManager::BUTTON::C,
			InputManager::BUTTON::D,
			InputManager::BUTTON::E };
		
		for (unsigned b = 0; b<=5; ++b) {
			auto button = buttons[b];
			
			if (static_cast<underlying_type<BUTTON>::type>(down)
				& static_cast<underlying_type<BUTTON>::type>(button)) {
				
				m_mtx.lock();
				
				m_buttonsDown.insert(button);
				
				// if button is in "cleared" it means the client already read it, so don't add it again until
				// we get button up, and then back down again
				if (m_buttonsPressedCleared.count(button) == 0) {
					m_buttonsPressed.insert(button);
				}
				
				m_mtx.unlock();
			}
			else {
				m_buttonsDown.erase(button);
				m_buttonsPressedCleared.erase(button);
			}
		}
		
		Sleep(10);
	}
}

/**************************************************************************************
     Static
 **************************************************************************************/

InputManager::BUTTON ButtonShimDown() {
	
	static const unsigned char I2C_ADDRESS = 0x3f;
	static const unsigned char REG_INPUT = 0x00;

	static int fd = -1;
	char *fileName = (char *)"/dev/i2c-1";
	
	if (fd == -1) {
		// Open port for reading and writing
		if ((fd = open(fileName, O_RDWR)) < 0) {
			printf("Failed to open button shim I2C bus.\n");
			exit(1);
		}
		
		// Set the port options and set the address of the device
		if (ioctl(fd, I2C_SLAVE, I2C_ADDRESS) < 0) {		
			printf("Failed to get button shim I2C device port.\n");
			close(fd);
			exit(1);
		}
	}
	
	unsigned char buttons = ~((i2c_smbus_read_byte_data(fd, REG_INPUT) << 27) >> 27);

	return static_cast<InputManager::BUTTON>(buttons);
}

void Sleep(unsigned milliseconds) {
	
	usleep(milliseconds * 1000);
}
