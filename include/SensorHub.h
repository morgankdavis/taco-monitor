//
//  SensorHub.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef SensorHub_h
#define SensorHub_h


#include <mutex>
#include <thread>


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

		unsigned ambientLight();
		float ambientTemperature();
		void shutdown();
		
	private:
		
		/**************************************************************************************
		     Private
		 **************************************************************************************/

		void updateLoop();
		
		std::mutex			m_mtx;
		std::thread			m_updateThread;
		bool				m_stop;
		
		unsigned 			m_ambientLight;
		float				m_ambientTemperature;
	};
}


#endif /* SensorHub_h */
