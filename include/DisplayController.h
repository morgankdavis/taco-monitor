//
//  DisplayController.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef DisplayController_h
#define DisplayController_h


namespace tacomon {

	class DisplayController {
		
	public:
		
		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		DisplayController();
		DisplayController(DisplayController&& other) = delete; // move initialization
		DisplayController(const DisplayController& other) = delete; // copy initialization
		DisplayController& operator= (DisplayController&& other) = delete; // move assignment
		DisplayController& operator= (const DisplayController& other) = delete; // copy assignment
		~DisplayController();
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/

		
		// private:
		
		/**************************************************************************************
		     Private
		 **************************************************************************************/
		
	};
}


#endif /* DisplayController_h */
