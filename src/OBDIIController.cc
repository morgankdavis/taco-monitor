//
//  OBDIIController.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/22/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "OBDIIController.h"

#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>


using namespace std;
using namespace tacomon;
using namespace serial;


constexpr const char* PORT =			"/dev/rfcomm0";
constexpr unsigned long BAUD_RATE =		115200;
constexpr unsigned TIMEOUT = 			1000;


/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

void Sleep(unsigned milliseconds);

/**************************************************************************************
     Lifecycle
 **************************************************************************************/

OBDIIController::OBDIIController():
	m_serial(nullptr),
	m_rpm(0) {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

bool OBDIIController::connect() {
	
	try {
		m_serial = make_shared<Serial>(PORT, BAUD_RATE, Timeout::simpleTimeout(TIMEOUT));
		
		cout << "Created serial device." << endl;
		
		if (m_serial->isOpen()) {
			
			cout << "Serial device connected." << endl;
			
			Sleep(2000);
			
			//		AT L 1 // linefeed on
			//		AT H 1 // headers on
			//		AT S 1 // slow, 5 baud initiation
			//		AT A L // allow long (> 7 byte) messages
			//		AT SP 0 // ATSP00 == erase stored protocol...?
			
			string writeStr = "";
			string readStr = string();
			
			// 'AT L 1' -- linefeed on
			
			writeStr = "AT L 1\n";
			cout << "writeStr: " << writeStr << endl;
			size_t bytesWritten = m_serial->write(writeStr);
			Sleep(2000);
			size_t bytesRead =  m_serial->readline(readStr);
			cout << "readStr: " << readStr << endl;
			readStr = "";

			// 'AT S 1' -- slow, 5 baud initiation
			
			writeStr = "AT S 1\n";
			cout << "writeStr: " << writeStr << endl;
			bytesWritten = m_serial->write(writeStr);
			Sleep(2000);
			bytesRead =  m_serial->readline(readStr);
			cout << "readStr: " << readStr << endl;
			readStr = "";
			
			// 'AT A L' -- allow long (> 7 byte) messages
			
			writeStr = "AT A L\n";
			cout << "writeStr: " << writeStr << endl;
			bytesWritten = m_serial->write(writeStr);
			Sleep(2000);
			bytesRead =  m_serial->readline(readStr);
			cout << "readStr: " << readStr << endl;
			readStr = "";
			
			// 'AT SP 0' -- ATSP00 == erase stored protocol
			
			writeStr = "AT SP 0\n";
			cout << "writeStr: " << writeStr << endl;
			bytesWritten = m_serial->write(writeStr);
			Sleep(2000);
			bytesRead =  m_serial->readline(readStr);
			cout << "readStr: " << readStr << endl;
			readStr = "";
			
			
			
			// 'AT RV' -- read voltage
			
			writeStr = "AT RV\n";
			cout << "writeStr: " << writeStr << endl;
			bytesWritten = m_serial->write(writeStr);
			Sleep(2000);
			bytesRead =  m_serial->readline(readStr);
			cout << "readStr: " << readStr << endl;
			
			
			
			//string result = m_serial->read(writeStr()+1);
			
			//			cout << "Iteration: " << count << ", Bytes written: ";
			//			cout << bytes_wrote << ", Bytes read: ";
			//			cout << result.length() << ", String read: " << result << endl;
			
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
	
	if (m_serial->isOpen()) {
		m_serial->close();
	}
}

void OBDIIController::printPorts() const {
	
	vector<PortInfo> devices_found = list_ports();
	vector<PortInfo>::iterator iter = devices_found.begin();
	
	while (iter != devices_found.end()) {
		PortInfo device = *iter++;
		
		printf("(%s, %s, %s)\n",
			   device.port.c_str(),
			   device.description.c_str(),
			   device.hardware_id.c_str() );
	}
}

unsigned OBDIIController::rpm() const {
	
	return m_rpm;
}

/**************************************************************************************
     Private
 **************************************************************************************/

void update() {
	
	// rpm
	
//	while (count < 10) {
//		size_t bytes_wrote = my_serial.write(test_string);
//		
//		string result = my_serial.read(test_string.length()+1);
//		
//		cout << "Iteration: " << count << ", Bytes written: ";
//		cout << bytes_wrote << ", Bytes read: ";
//		cout << result.length() << ", String read: " << result << endl;
//		
//		count += 1;
//	}
}

/**************************************************************************************
     Static
 **************************************************************************************/

void Sleep(unsigned milliseconds) {
	usleep(milliseconds * 1000);
}
