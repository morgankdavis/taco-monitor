//
//  SensorHub.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef SensorHub_h
#define SensorHub_h


namespace tacomon {

	class SensorHub {
		
	public:
		
		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		SensorHub();
		SensorHub(SensorHub&& other) = delete; // move initialization
		SensorHub(const SensorHub& other) = delete; // copy initialization
		SensorHub& operator= (SensorHub&& other) = delete; // move assignment
		SensorHub& operator= (const SensorHub& other) = delete; // copy assignment
		~SensorHub();
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/

		
		// private:
		
		/**************************************************************************************
		     Private
		 **************************************************************************************/

	};
}


#endif /* SensorHub_h */
