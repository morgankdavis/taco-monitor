//
//  OBDIIController.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/22/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "OBDIIController.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <unistd.h>


using namespace std;
using namespace tacomon;
using namespace serial;


constexpr const char* COMM_PORT =				"/dev/rfcomm0";
constexpr unsigned long BAUD_RATE =				115200;
constexpr unsigned TIMEOUT = 					250; // ms

constexpr float VOLTAGE_UPDATE_PERIOD =			120; // seconds
constexpr float RPM_UPDATE_PERIOD =				0;
constexpr float COOLANT_TEMP_UPDATE_PERIOD =	10;
constexpr float SPEED_UPDATE_PERIOD =			0;


/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

static string Tail(string const& source, size_t const length);
static unsigned ParsedLineNumber(string const& line, unsigned length);
static unsigned UnsignedFromHexString(string const& str);
static float Time();
static void Sleep(unsigned milliseconds);

/**************************************************************************************
     Lifecycle
 **************************************************************************************/

OBDIIController::OBDIIController():
	m_serial(nullptr),
	m_connected(false),
	m_voltage(0),
	m_rpm(0),
	m_coolantTemp(1000),
	m_speed(0) {
	
}

//OBDIIController::OBDIIController(OBDIIController&& other) { // move initialization
//	lock_guard<mutex> lock(other.m_mtx);
//	//value = std::move(other.value);
//	//other.value = 0;
//}
//
//OBDIIController::OBDIIController(const OBDIIController& other) { // copy initialization
//	lock_guard<mutex> lock(other.m_mtx);
//	//value = other.value;
//}
//
//OBDIIController& OBDIIController::operator= (OBDIIController&& other) { // move assignment
//	std::lock(m_mtx, other.m_mtx);
//	lock_guard<mutex> self_lock(m_mtx, adopt_lock);
//	lock_guard<mutex> other_lock(other.m_mtx, adopt_lock);
////	value = move(other.value);
////	other.value = 0;
//	return *this;
//}
//
//OBDIIController& OBDIIController::operator= (const OBDIIController& other) { // copy assignment
//	lock(m_mtx, other.m_mtx);
//	lock_guard<mutex> self_lock(m_mtx, adopt_lock);
//	lock_guard<mutex> other_lock(other.m_mtx, adopt_lock);
////	value = other.value;
//	return *this;
//}

OBDIIController::~OBDIIController() {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

bool OBDIIController::connect() {
	
	// sudo rfcomm connect rfcomm0 00:1D:A5:00:D1:91
	
	try {
		cout << "Opening OBD-II serial connection..." << endl;
		
		m_serial = make_unique<Serial>(COMM_PORT, BAUD_RATE, Timeout::simpleTimeout(TIMEOUT));
		
		if (m_serial->isOpen()) {
			
			cout << "Serial connection open." << endl;
			
			// 'AT L 1' -- linefeed on
			
			writeLine("AT L 1");
			auto result = readLines();
			
			// 'AT H 0' -- headers off
			
			writeLine("AT H 0");
			result = readLines();

			// 'AT S 1' -- slow, 5 baud initiation

			writeLine("AT S 1");
			result = readLines();

			// 'AT A L' -- allow long (> 7 byte) messages

			writeLine("AT A L");
			result = readLines();

			// 'AT SP 0' -- ATSP00 == erase stored protocol

			writeLine("AT SP 0");
			result = readLines();
			
			
			// force ELM to do the handshake
			
			writeLine("01 05"); // COOLANT TEMP
			
			Sleep(7000);
			
			auto rpmLines = readLines();
			for (auto line : rpmLines) {
				cout << "line: " << line << endl;
			}
			
			if (rpmLines[1] == "UNABLE TO CONNECT") {
				cout << "Unable to read data." << endl;
				return false;
			}
			
			m_mtx.lock();
			m_connected = true;
			m_mtx.unlock();
			
			m_updateThread = thread(&OBDIIController::updateLoop, this);
			
			return true;
		}
	}
	catch (exception &e) {
		cerr << "Exception in OBDIIController: " << e.what() << endl;
		return false;
	}
	
	return false;
}

void OBDIIController::disconnect() {

	if (m_mtx.lock(), m_serial->isOpen()) {
		m_mtx.unlock();
		cout << "Closing serial connection..." << endl;
		
		m_mtx.lock();
		m_connected = false;
		m_mtx.unlock();
		cout << "Waiting for update to complete..." << endl;
		m_updateThread.join();
		
		m_serial->close();
		
		cout << "Connection closed." << endl;
		
		m_serial = nullptr;
	}
}

bool OBDIIController::connected() {
	
	lock_guard<mutex> guard(m_mtx);
	
	return m_connected;
}

float OBDIIController::voltage() {
	
	lock_guard<mutex> guard(m_mtx);
	
	return m_voltage;
}

unsigned OBDIIController::rpm() {
	
	lock_guard<mutex> guard(m_mtx);
	
	return m_rpm;
}

unsigned OBDIIController::coolantTemp() {
	
	lock_guard<mutex> guard(m_mtx);
	
	return m_coolantTemp;
}

unsigned OBDIIController::speed() {
	
	lock_guard<mutex> guard(m_mtx);
	
	return m_speed;
}

/**************************************************************************************
     Private
 **************************************************************************************/

void OBDIIController::updateLoop() {
	
	while (m_mtx.lock(), m_connected) {
		m_mtx.unlock();
		update();
	}
}

void OBDIIController::update() {
	
	float time = Time();
	
	// battery voltage
	
	static float voltageUpdateTime = -1;
	time = Time();
	if ((voltageUpdateTime == -1) || (time - voltageUpdateTime > VOLTAGE_UPDATE_PERIOD)) {

		writeLine("AT RV");
		auto voltsLine = readLines().front();
		voltsLine.erase(remove(voltsLine.begin(), voltsLine.end(), 'V'), voltsLine.end());
		cout << "voltsLine: " << voltsLine << endl;
		char* endPtr;
		auto volts = strtof(voltsLine, endPtr);
		m_mtx.lock();
		m_voltage = volts;
		m_mtx.unlock();
		
		voltageUpdateTime = time;
	}
	
	// rpm
	
	static float rpmUpdateTime = -1;
	time = Time();
	if ((rpmUpdateTime == -1) || (time - rpmUpdateTime > RPM_UPDATE_PERIOD)) {

		writeLine("01 0C");
		auto rpm = lroundf(((float)ParsedLineNumber(readLines().front(), 2)) / 4.0);
		//cout << "rpm: " << rpm << endl;
		m_mtx.lock();
		m_rpm = rpm;
		m_mtx.unlock();
		
		rpmUpdateTime = time;
	}
	
	// speed
	
	static float speedUpdateTime = -1;
	time = Time();
	if ((speedUpdateTime == -1) || (time - speedUpdateTime > SPEED_UPDATE_PERIOD)) {

		writeLine("01 0D");
		auto kph = ParsedLineNumber(readLines().front(), 1);
		//cout << "kph: " << kph << endl;
		m_mtx.lock();
		m_speed = kph;
		m_mtx.unlock();
		
		speedUpdateTime = time;
	}
	
	// coolant temp
	
	static float coolantTempUpdateTime = -1;
	time = Time();
	if ((coolantTempUpdateTime == -1) || (time - coolantTempUpdateTime > COOLANT_TEMP_UPDATE_PERIOD)) {

		writeLine("01 05");
		auto temp = ParsedLineNumber(readLines().front(), 1) - 40;
		//cout << "temp: " << temp << " deg C" << endl;
		m_mtx.lock();
		m_coolantTemp = temp;
		m_mtx.unlock();
		
		coolantTempUpdateTime = time;
	}
	
	
	cout << endl << endl;
}

void OBDIIController::writeLine(string line) {
	
	//lock_guard<mutex> guard(m_mtx);
	
	if (m_serial->isOpen()) {
		auto writeStr = line + "\n\r";
		cout << "-> '" << line << "'" << endl;
		m_serial->write(writeStr);
	}
	else {
		cout << "Serial connection not open." << endl;
	}
}

vector<string> OBDIIController::readLines() {
	
	//lock_guard<mutex> guard(m_mtx);
	
	auto result = vector<string>();
	
	if (m_serial->isOpen()) {
		auto readLines = m_serial->readlines();
		auto tail = vector<string>(readLines.begin()+2, readLines.end());
		
		for (string line : tail) {

			line.erase(remove(line.begin(), line.end(), '\n'), line.end());

			if (line.length() >= 2) {
				cout << line << endl;
				result.push_back(line);
			}
		}
	}
	else {
		cout << "Serial connection not open." << endl;
	}
	
	return result;
}

/**************************************************************************************
     Static
 **************************************************************************************/

string Tail(string const& source, size_t const length) {
	
	if (length >= source.size()) {
		return source;
	}
	
	return source.substr(source.size() - length);
}

unsigned ParsedLineNumber(string const& line, unsigned length) {

	auto lineCopy = line;
	lineCopy.erase(remove(lineCopy.begin(), lineCopy.end(), ' '), lineCopy.end());
	auto tail = Tail(lineCopy, length * 2 + 1);
	return UnsignedFromHexString(tail);
}

unsigned UnsignedFromHexString(string const& str) {
	
	unsigned result;   
	stringstream ss;
	ss << hex << str;
	ss >> result;
	return result;
}

float Time() {

	static auto startDate = chrono::high_resolution_clock::now();
	auto nowDate = chrono::high_resolution_clock::now();
	return (chrono::duration<float>(nowDate - startDate)).count();
}

void Sleep(unsigned milliseconds) {
	
	usleep(milliseconds * 1000);
}
