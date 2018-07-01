//
//  DisplayController.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef DisplayController_h
#define DisplayController_h


#include <memory>
#include <string>


namespace tacomon {
	
	
//	class Beeper;
	

	class DisplayController {
		
	public:
		
		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		DisplayController();//std::shared_ptr<Beeper> beeper);
		DisplayController(DisplayController&& other) = delete; // move initialization
		DisplayController(const DisplayController& other) = delete; // copy initialization
		DisplayController& operator= (DisplayController&& other) = delete; // move assignment
		DisplayController& operator= (const DisplayController& other) = delete; // copy assignment
		~DisplayController();
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/

		void display(std::string str);
		void fill();
		//void alert(std::string str);
		
		void brightness(float percent);
		float brightness() const;
		
		std::string displayString() const;
		
		//bool alerting() const;
		
		void shutdown();
		
	private:
		
		/**************************************************************************************
		     Private
		 **************************************************************************************/
		
		//std::shared_ptr<Beeper> 		m_beeper;
		float							m_brightness;
		std::string						m_displayString;
		//bool							m_alerting;
	};
}


#endif /* DisplayController_h */
