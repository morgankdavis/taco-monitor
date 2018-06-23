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

#include "serial/serial.h"


namespace tacomon {

	class OBDIIController {
		
	public:
		
		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		OBDIIController();
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/
		
		bool connect();
		void disconnect();
		void printPorts() const;
		unsigned rpm() const;
		
		// private:
		
		/**************************************************************************************
		     Private
		 **************************************************************************************/
		
		void update();
		
	private:
		
		std::shared_ptr<serial::Serial>		m_serial;
		unsigned 							m_rpm;
	};
}


#endif /* OBDIIController_h */
