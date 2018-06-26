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

#include "smbus.h"

#include "InputManager.h"
#include "OBDIIController.h"
#include "SensorHub.h"


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
     Types
 **************************************************************************************/



/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

static void SetupPython();
static void ExecPython(string python);
static void TerminatePython();
static void DisplayString(string str);
static void DisplaySmallString(unsigned display, string str);
static void FillDisplay(bool fill);
static void SetupGPIO();
static void Sleep(unsigned milliseconds);

/**************************************************************************************
     Lifecycle
 **************************************************************************************/

TacoMonitor::TacoMonitor():
	m_inputManager(make_shared<InputManager>()),
	m_obdiiController(make_shared<OBDIIController>()),
	m_sensorHub(make_shared<SensorHub>()),
	m_stop(false) {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

int TacoMonitor::start(const vector<string>& args) {
	
	SetupPython();
	SetupGPIO();
	
//	if (!m_obdiiController->connect()) {
//		cout << "Couldn't create OBD-II serial connection." << endl;
//	}
	
	cout << "Ready." << endl;

	while (!m_stop) {
		update();
	}
	
	shutdown();
	
//	if (m_obdiiController->connected()) {
//		m_obdiiController->updateThread().join();
//	}
}

void TacoMonitor::stop() {
	cout << "TacoMonitor::stop()" << endl;
	
	m_stop = true;
}

/**************************************************************************************
     Private
 **************************************************************************************/

void TacoMonitor::update() {

	if (m_inputManager->buttonDown(InputManager::BUTTON::A)) {
		//DisplayString("     A");
		
		char tempStr[32];
		sprintf(tempStr, "T %.1f", m_sensorHub->ambientTemperature() * (9.0/5.0) + 32);
		DisplayString(tempStr);
	}
	if (m_inputManager->buttonDown(InputManager::BUTTON::B)) {
		//DisplayString("    B");
		
		char luxStr[32];
		sprintf(luxStr, "L %d", m_sensorHub->ambientLight());
		DisplayString(luxStr);
	}
	if (m_inputManager->buttonDown(InputManager::BUTTON::C)) {
		DisplayString("   C");
	}
	if (m_inputManager->buttonDown(InputManager::BUTTON::D)) {
		DisplayString("  D");
	}
	if (m_inputManager->buttonDown(InputManager::BUTTON::E)) {
		digitalWrite(BUZZER_BCM_PIN, LOW); // low == on
		DisplayString(" E");
	}
	else {
		digitalWrite(BUZZER_BCM_PIN, HIGH); // low == on
	}
	
	if (!m_inputManager->buttonsDown().size()) {
		DisplayString("");
	}

//	auto lux = LightLevel();
//	cout << "lux: " << lux << endl;
	
//	stringstream displayStream;
//	displayStream.width(6);
//	displayStream << right << m_obdiiController->rpm();
//	auto displayStr = displayStream.str();
//	
//	DisplayString(displayStr);
	
//	bool aDown = ButtonADown();
	
//	FillDisplay(true);
//	
//	digitalWrite(BUZZER_BCM_PIN, LOW); // low == on
//	delay(BUZZER_PERIOD/2);
//	
//	DisplayString("DICKS");
//	
//	digitalWrite(BUZZER_BCM_PIN, HIGH);
//	delay(BUZZER_PERIOD/2);
}

void TacoMonitor::shutdown() {
	cout << "TacoMonitor::shutdown()" << endl;
	
	digitalWrite(BUZZER_BCM_PIN, HIGH);
	
	DisplayString("");
	
	m_inputManager->shutdown();
	m_sensorHub->shutdown();
	
	TerminatePython();
	
	m_obdiiController->disconnect();
}

/**************************************************************************************
     Static
 **************************************************************************************/

void SetupPython() {
	
	cout << "Starting Python..." << endl;
	
	Py_SetProgramName((wchar_t*)"taco_mon_python");  /* optional but recommended */
	Py_Initialize();
	PyRun_SimpleString("import smbus\n"
					   "from time import sleep\n"
					   "from microdotphat import clear, set_brightness, show, write_string, draw_tiny, fill, WIDTH, HEIGHT\n");
}

void ExecPython(string python) {
	
	PyRun_SimpleString(python.c_str());
}

void TerminatePython() {
	
	cout << "Terminating Python..." << endl;
	
	Py_Finalize();
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
	
	cout << "Setting up GPIO..." << endl;
	
	wiringPiSetupGpio(); // use BCM pin numbers
	// http://wiringpi.com/reference/
	pinMode(BUZZER_BCM_PIN, OUTPUT);
	digitalWrite(BUZZER_BCM_PIN, HIGH); // high == off
}

void Sleep(unsigned milliseconds) {
	
	usleep(milliseconds * 1000);
}
