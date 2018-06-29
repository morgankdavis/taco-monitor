//
//  Beeper.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef Beeper_h
#define Beeper_h


namespace tacomon {

	class Beeper {
		
	public:
		
		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		Beeper();
		Beeper(Beeper&& other) = delete; // move initialization
		Beeper(const Beeper& other) = delete; // copy initialization
		Beeper& operator= (Beeper&& other) = delete; // move assignment
		Beeper& operator= (const Beeper& other) = delete; // copy assignment
		~Beeper();
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/
		
		void start();
		void stop();
		
		bool beeping() const;
		
	private:

		/**************************************************************************************
		     Private
		 **************************************************************************************/
		
		bool	m_beeping;
	};
}


#endif /* Beeper_h */
