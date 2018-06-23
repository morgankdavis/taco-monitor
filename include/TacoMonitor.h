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


namespace tacomon {
	
	
	class OBDIIController;
	

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
		
		void update();
		void shutdown();
		
		std::shared_ptr<OBDIIController>	m_obdiiController;
		
		bool								m_stop;
	};
}


#endif /* TacoMonitor_h */
