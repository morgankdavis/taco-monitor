//
//  TacoMonitor.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/14/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef TacoMonitor_h
#define TacoMonitor_h


#include <memory>
#include <string>
#include <vector>


#define DEBUGGING


namespace tacomon {
	
	
	class Beeper;
	class DisplayController;
	class InputManager;
	class OBDIIController;
	class SensorHub;
	

	class TacoMonitor {
		
	public:
		
		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		TacoMonitor();
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/
		
		int start(const std::vector<std::string>& args);
		void stop();
		
	private:
		
		/**************************************************************************************
		     Private
		 **************************************************************************************/

		enum class DISPLAY_MODE : int {
			CLOCK = 				0,
			RPM = 					1,
			SPEED = 				2,
			COOLANT_TEMP = 			3,
			BATTERY_VOLTAGE =		4,
//			AMBIENT_TEMP = 			5,
//			RUNTIME = 				6,
#ifdef DEBUGGING
			AMBIENT_BRIGHTNESS= 	6
#endif
		};
		
		void update();
		void shutdown();
		
		std::shared_ptr<InputManager>			m_inputManager;
		std::shared_ptr<OBDIIController>		m_obdiiController;
		std::shared_ptr<SensorHub>				m_sensorHub;
		std::shared_ptr<Beeper>					m_beeper;
		std::shared_ptr<DisplayController>		m_displayController;
		DISPLAY_MODE							m_displayMode;
		bool									m_stop;
	};
}


#endif /* TacoMonitor_h */
