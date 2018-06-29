//
//  TacoMonitor.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/14/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "TacoMonitor.h"

#include <ctime>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Beeper.h"
#include "DisplayController.h"
#include "InputManager.h"
#include "OBDIIController.h"
#include "SensorHub.h"


using namespace std;
using namespace tacomon;


/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

static string TimeString();
static void Sleep(unsigned milliseconds);

/**************************************************************************************
     Lifecycle
 **************************************************************************************/

TacoMonitor::TacoMonitor():
	m_inputManager(make_shared<InputManager>()),
	m_obdiiController(make_shared<OBDIIController>()),
	m_sensorHub(make_shared<SensorHub>()),
	m_beeper(make_shared<Beeper>()),
	m_displayController(make_shared<DisplayController>(m_beeper)),
	m_displayMode(DISPLAY_MODE::CLOCK),
	m_stop(false) {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

int TacoMonitor::start(const vector<string>& args) {

	if (!m_obdiiController->connect()) {
		cout << "Couldn't create OBD-II serial connection." << endl;
		
		m_displayController->display("OBDERR");
		Sleep(5000);
	}
	
	cout << "Ready." << endl;

	while (!m_stop) {
		update();
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
	
	if (m_inputManager->buttonPressed(InputManager::BUTTON::A)) {
		auto modeRaw = static_cast<underlying_type<DISPLAY_MODE>::type>(m_displayMode);
		++modeRaw;
		if (modeRaw > static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::RUNTIME)) {
			modeRaw = static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::CLOCK);
		}
		m_displayMode = static_cast<DISPLAY_MODE>(modeRaw);
	}
	else if (m_inputManager->buttonPressed(InputManager::BUTTON::B)) {
		auto modeRaw = static_cast<underlying_type<DISPLAY_MODE>::type>(m_displayMode);
		--modeRaw;
		if (modeRaw < static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::CLOCK)) {
			modeRaw = static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::RUNTIME);
		}
		m_displayMode = static_cast<DISPLAY_MODE>(modeRaw);
	}

	string displayStr = "";
	
	switch (m_displayMode) {
		
		case DISPLAY_MODE::CLOCK: {
			stringstream displayStream;
			displayStream.width(6);
			displayStream << right << TimeString();
			displayStr = displayStream.str();
			break; }
		
		case DISPLAY_MODE::RPM: {
			stringstream displayStream;
			displayStream.width(6);
			displayStream << right << m_obdiiController->rpm();
			displayStr = displayStream.str();
			displayStr.replace(0, 1, "R");
			break; }
		
		case DISPLAY_MODE::SPEED: {
			auto speedMPH = lroundf(m_obdiiController->speed() * 0.6213);
			stringstream displayStream;
			displayStream.width(6);
			displayStream << right << speedMPH;
			displayStr = displayStream.str();
			displayStr.replace(0, 1, "S");
			break; }
		
		case DISPLAY_MODE::COOLANT_TEMP: {
			auto tempC = m_obdiiController->coolantTemp();
			auto tempF = 0;
			if (tempC != 1000) { // 1000 == not initialized
				tempF = lroundf(tempC * (9.0/5.0) + 32);
			}
			stringstream displayStream;
			displayStream.width(6);
			displayStream << right << tempF;
			displayStr = displayStream.str();
			displayStr.replace(0, 1, "C");
			break; }
		
		case DISPLAY_MODE::BATTERY_VOLTAGE: {
			stringstream displayStream;
			displayStream.width(6);
			char voltsStr[32];
			sprintf(voltsStr, "%.1f", m_obdiiController->voltage());
			displayStream << voltsStr;
			//displayStream << right << fixed << setprecision(1) << m_obdiiController->voltage();
			displayStr = displayStream.str();
			displayStr.replace(0, 1, "V");
			break; }
		
		case DISPLAY_MODE::AMBIENT_TEMP: {
			auto tempF = lroundf(m_sensorHub->ambientTemperature() * (9.0/5.0) + 32);
			stringstream displayStream;
			displayStream.width(6);
			displayStream << right << fixed << setprecision(1) << tempF;
			displayStr = displayStream.str();
			displayStr.replace(0, 1, "A");
			break; }
			
		case DISPLAY_MODE::RUNTIME: {
			displayStr = "RUN";
			break; }
	}
	
	m_displayController->display(displayStr);

//	FillDisplay(true);
//	
//	digitalWrite(BUZZER_BCM_PIN, LOW); // low == on
//	delay(BUZZER_PERIOD/2);
//	
//	DisplayString("DICKS");
//	
//	digitalWrite(BUZZER_BCM_PIN, HIGH);
//	delay(BUZZER_PERIOD/2);
	
	Sleep(50);
}

void TacoMonitor::shutdown() {
	cout << "TacoMonitor::shutdown()" << endl;
	
	m_displayController->shutdown();
	m_inputManager->shutdown();
	m_sensorHub->shutdown();
	m_obdiiController->disconnect();
}

/**************************************************************************************
     Static
 **************************************************************************************/

string TimeString() {
	
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	
	strftime(buffer, sizeof(buffer), "%l:%M", timeinfo);
	
	return string(buffer);
}

void Sleep(unsigned milliseconds) {
	
	usleep(milliseconds * 1000);
}
