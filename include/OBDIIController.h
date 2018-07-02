//
//  OBDIIController.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/22/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef OBDIIController_h
#define OBDIIController_h

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "serial/serial.h"


namespace tacomon {

	class OBDIIController {
		
	public:
		
		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		OBDIIController();
		OBDIIController(OBDIIController&& other) = delete; // move initialization
		OBDIIController(const OBDIIController& other) = delete; // copy initialization
		OBDIIController& operator= (OBDIIController&& other) = delete; // move assignment
		OBDIIController& operator= (const OBDIIController& other) = delete; // copy assignment
		~OBDIIController();
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/
		
		bool connect();
		void disconnect();
		bool connected();
		float voltage();
		unsigned rpm();
		unsigned coolantTemp(); // deg c
		unsigned speed(); // kph
		
	private:
		
		/**************************************************************************************
		     Private
		 **************************************************************************************/
		
		void updateLoop();
		void update();
		void writeLine(std::string line);
		std::vector<std::string> readLines();

		std::unique_ptr<serial::Serial>		m_serial;
		bool								m_connected;
		std::mutex							m_mtx;
		std::thread							m_updateThread;
		float 								m_voltage;
		unsigned 							m_rpm;
		unsigned 							m_coolantTemp;
		unsigned 							m_speed;
	};
}


#endif /* OBDIIController_h */
