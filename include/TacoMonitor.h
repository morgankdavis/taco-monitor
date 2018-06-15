//
//  TacoMonitor.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/14/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef TacoMonitor_h
#define TacoMonitor_h


//#include <mutex>
#include <string>
#include <vector>


namespace tacomon {

	class TacoMonitor {
		
	public:
		
		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		TacoMonitor()
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/
		
		int start(const std::vector<std::string>& args);
		void update();
		void TacoMonitor::stop();
		
	private:
		
		//std::mutex		m_buttonMutex;
		bool			m_stop;
		
	};
}


#endif /* TacoMonitor_h */
