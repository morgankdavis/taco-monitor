//
//  TacoMonitor.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/14/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "TacoMonitor.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Beeper.h"
#include "DisplayController.h"
#include "InputManager.h"
#include "OBDIIController.h"
#include "SensorHub.h"


using namespace std;
using namespace tacomon;


/**************************************************************************************
     Constants
 **************************************************************************************/

//constexpr unsigned REDLINE =			5450; // rpm
//constexpr unsigned MAX_COOLANT_TEMP =	195; // deg F
//constexpr float MIN_VOLTAGE_RUNNING =	13.5; // volts
//constexpr float MIN_VOLTAGE_ACC =		11.0; // volts

constexpr unsigned REDLINE =			2000; // rpm
constexpr unsigned MAX_COOLANT_TEMP =	160; // deg F
constexpr float MIN_VOLTAGE_RUNNING =	13.5; // volts
constexpr float MIN_VOLTAGE_ACC =		11.0; // volts

#ifdef DEBUGGING
constexpr float MIN_AMBIENT_LIGHT = 	50; // lux
#endif

constexpr unsigned ALERT_PERIOD =		1500; // ms

/**************************************************************************************
     Types
 **************************************************************************************/

enum class ALERT_PHASE {
	OFF,
	BEEP,
	LABEL
};

/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

static float Time();
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
	m_displayController(make_shared<DisplayController>()),
	m_displayMode(DISPLAY_MODE::CLOCK),
	m_stop(false) {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

int TacoMonitor::start(const vector<string>& args) {

	if (!m_obdiiController->connect()) {
		cout << "Couldn't create OBD-II serial connection." << endl;
		
		m_beeper->on();
		m_displayController->display("OBDERR");
		Sleep(5000);
		m_beeper->off();
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
#ifdef DEBUGGING
		if (modeRaw > static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::AMBIENT_BRIGHTNESS)) {
#else
		if (modeRaw > static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::AMBIENT_TEMP)) {
#endif
			modeRaw = static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::CLOCK);
		}

		m_displayMode = static_cast<DISPLAY_MODE>(modeRaw);
	}
	else if (m_inputManager->buttonPressed(InputManager::BUTTON::B)) {
		auto modeRaw = static_cast<underlying_type<DISPLAY_MODE>::type>(m_displayMode);
		--modeRaw;
		if (modeRaw < static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::CLOCK)) {
#ifdef DEBUGGING
			modeRaw = static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::AMBIENT_BRIGHTNESS);
#else
			modeRaw = static_cast<underlying_type<DISPLAY_MODE>::type>(DISPLAY_MODE::AMBIENT_TEMP);
#endif
		}
		m_displayMode = static_cast<DISPLAY_MODE>(modeRaw);
	}
		
	DISPLAY_MODE presentationDisplayMode = m_displayMode;
	
	auto rpm = m_obdiiController->rpm();
	auto speedMPH = lroundf(m_obdiiController->speed() * 0.6213);
	auto coolantTempC = m_obdiiController->coolantTemp();
	auto coolantTempF = 0;
	if (coolantTempC != 1000) { // 1000 == not initialized
		coolantTempF = lroundf(coolantTempC * (9.0/5.0) + 32);
	}
	auto batteryVoltage = m_obdiiController->voltage();
	auto ambientTempF = lroundf(m_sensorHub->ambientTemperature() * (9.0/5.0) + 32);
	
	auto lux = m_sensorHub->ambientLight();
		
		
		
		// TEMPORARY
		
		stringstream displayStream;
		displayStream.width(6);
		char voltsStr[32];
		cout << "batteryVoltage: " << batteryVoltage << endl;
		sprintf(voltsStr, "%.1f", batteryVoltage);
		cout << "voltsStr: " << voltsStr << endl;
		displayStream << voltsStr;
		string displayStr = displayStream.str();
		displayStr.replace(0, 1, "B");
		cout << "displayStr: " << displayStr << endl;
		
		
		
		
		
	// check alarms, in order of severity
	// 1. redline
	// 2. coolant temp
	// 3. battery voltage

	static ALERT_PHASE alertPhase = ALERT_PHASE::OFF;
	
	bool alerting = false;
	bool rpmAlerting = false;
//	if (m_obdiiController->connected() && rpm > REDLINE) {
//		cout << "--- REDLINE ---" << endl;
//		alerting = true;
//		rpmAlerting = true;
//		presentationDisplayMode = DISPLAY_MODE::RPM;
//	}
//	else if (!alerting && (m_obdiiController->connected() && coolantTempF > MAX_COOLANT_TEMP)) {
//		cout << "--- COOLANT TEMP ---" << endl;
//		alerting = true;
//		presentationDisplayMode = DISPLAY_MODE::COOLANT_TEMP;
//	}
//	else if (!alerting && (m_obdiiController->connected() && (rpm > 10) && batteryVoltage < MIN_VOLTAGE_RUNNING)) {
//		cout << "--- RUNNING VOLTAGE ---" << endl;
//		alerting = true;
//		presentationDisplayMode = DISPLAY_MODE::BATTERY_VOLTAGE;
//	}
//	else if (!alerting && (m_obdiiController->connected() && (rpm <= 10) && batteryVoltage < MIN_VOLTAGE_ACC)) {
//		cout << "--- ACC VOLTAGE ---" << endl;
//		alerting = true;
//		presentationDisplayMode = DISPLAY_MODE::BATTERY_VOLTAGE;
//	}
//#ifdef DEBUGGING
//	else if (!alerting && lux < MIN_AMBIENT_LIGHT) {
//		cout << "--- AMBIENT LIGHT ---" << endl;
//		alerting = true;
//		presentationDisplayMode = DISPLAY_MODE::AMBIENT_BRIGHTNESS;
//	}
//#endif
//	else {
//		alertPhase = ALERT_PHASE::OFF;
//	}
		
	if (rpmAlerting) {
		alertPhase = ALERT_PHASE::OFF;
	}
	else {
		switch (alertPhase) {
			case ALERT_PHASE::OFF:
				if (alerting) alertPhase = ALERT_PHASE::BEEP;
				break;
			case ALERT_PHASE::BEEP:
				alertPhase = ALERT_PHASE::LABEL;
				break;
			case ALERT_PHASE::LABEL:
				alertPhase = ALERT_PHASE::BEEP;
				break;
		}
	}
		
	// set brightness
	if (alerting) {
		m_displayController->brightness(1.0);
	}
	else {
		m_displayController->brightness(0.5);
	}

	if (alerting && !rpmAlerting && alertPhase == ALERT_PHASE::BEEP) {
		m_beeper->on();
		m_displayController->fill();
	}
	else {
		string displayStr = "";
		
		if (rpmAlerting) {
			m_beeper->on();
		}
		else {
			m_beeper->off();
		}
		
		switch (presentationDisplayMode) {
					
			case DISPLAY_MODE::CLOCK: {
				stringstream displayStream;
				displayStream.width(6);
				displayStream << right << TimeString();
				displayStr = displayStream.str();
				break; }
				
			case DISPLAY_MODE::RPM: {
				stringstream displayStream;
				displayStream.width(6);
				displayStream << right << rpm;
				displayStr = displayStream.str();
				displayStr.replace(0, 1, "R");
				break; }
				
			case DISPLAY_MODE::SPEED: {
				stringstream displayStream;
				displayStream.width(6);
				displayStream << right << speedMPH;
				displayStr = displayStream.str();
				displayStr.replace(0, 1, "S");
				break; }
				
			case DISPLAY_MODE::COOLANT_TEMP: {
				stringstream displayStream;
				displayStream.width(6);
				displayStream << right << coolantTempF;
				displayStr = displayStream.str();
				displayStr.replace(0, 1, "C");
				break; }
				
			case DISPLAY_MODE::BATTERY_VOLTAGE: {
				stringstream displayStream;
				displayStream.width(6);
				char voltsStr[32];
				cout << "batteryVoltage: " << batteryVoltage << endl;
				sprintf(voltsStr, "%.1f", batteryVoltage);
				cout << "voltsStr: " << voltsStr << endl;
				displayStream << voltsStr;
				displayStr = displayStream.str();
				displayStr.replace(0, 1, "B");
				cout << "displayStr: " << displayStr << endl;
				break; }
				
			case DISPLAY_MODE::AMBIENT_TEMP: {
				stringstream displayStream;
				displayStream.width(6);
				displayStream << right << fixed << setprecision(1) << ambientTempF;
				displayStr = displayStream.str();
				displayStr.replace(0, 1, "A");
				break; }
				
//			case DISPLAY_MODE::RUNTIME: {
//				displayStr = "RUN";
//				break; }
				
			case DISPLAY_MODE::AMBIENT_BRIGHTNESS: {
				stringstream displayStream;
				displayStream.width(6);
				displayStream << lux;
				displayStr = displayStream.str();
				displayStr.replace(0, 1, "L");
				break; }
		}
		
		m_displayController->display(displayStr);
	}

	if (alerting) {
		Sleep(lroundf((float)ALERT_PERIOD/2.0));
	}
	else {
		Sleep(50);
	}
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

float Time() {
	
	static auto startDate = chrono::high_resolution_clock::now();
	auto nowDate = chrono::high_resolution_clock::now();
	return (chrono::duration<float>(nowDate - startDate)).count();
}

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
