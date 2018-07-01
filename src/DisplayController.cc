//
//  DisplayController.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "DisplayController.h"

#include <iostream>
#include <python3.5/Python.h>

//#include "Beeper.h"


using namespace std;
using namespace tacomon;


/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

static void StartPython();
static void ExecPython(string python);
static void TerminatePython();
static void DisplayString(string str);
static void FillDisplay(bool fill);
static void TurnOffButtonShimPixel();


/**************************************************************************************
     Lifecycle
 **************************************************************************************/

DisplayController::DisplayController()://shared_ptr<Beeper> beeper):
	//m_beeper(beeper),
	m_brightness(1.0),
m_displayString("") {//,
	//m_alerting(false) {
	
		StartPython();
		TurnOffButtonShimPixel();
}

DisplayController::~DisplayController() {
	shutdown();
}

/**************************************************************************************
     Public
 **************************************************************************************/

void DisplayController::display(std::string str) {
	
	m_displayString = str;
	//m_alerting = false;
	DisplayString(str);
}

void DisplayController::fill() {
	
	FillDisplay(true);
}

//void DisplayController::alert(std::string str) {
//	
//	m_displayString = str;
//	m_alerting = true;
//}

void DisplayController::brightness(float percent) {
	m_brightness = percent;
}

float DisplayController::brightness() const {
	return m_brightness;
}

string DisplayController::displayString() const {
	return m_displayString;
}

//bool DisplayController::alerting() const {
//	return m_alerting;
//}

void DisplayController::shutdown() {
	
	DisplayString("");
	TerminatePython();
}

/**************************************************************************************
     Private
 **************************************************************************************/


/**************************************************************************************
     Static
 **************************************************************************************/

void StartPython() {
	
	cout << "Starting Python..." << endl;
	
	Py_SetProgramName((wchar_t*)"taco_mon_python");  /* optional but recommended */
	Py_Initialize();
	PyRun_SimpleString("import smbus\n"
					   "from time import sleep\n"
					   "from buttonshim import set_pixel\n"
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

void FillDisplay(bool fill) {
	
	char execStr[1024];
	sprintf(execStr, "clear()\n" \
			"fill(%s)\n" \
			"show()\n", (fill ? "1" : "0"));
	ExecPython(execStr);
}

void TurnOffButtonShimPixel() {

	// this is hacky, but since this class owns the Python interpreter we'll do it here
	// sometimes the APA102 LED on the Pimoroni Button Shim lights up at power on... (?) Turn it off.

	char execStr[1024];
        sprintf(execStr, "set_pixel(0, 0, 0)");
        ExecPython(execStr);
}
