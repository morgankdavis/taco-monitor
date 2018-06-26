//
//  InputManager.h
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#ifndef InputManager_h
#define InputManager_h


#include <mutex>
#include <set>
#include <thread>


namespace tacomon {

	class InputManager {
		
		public:
		
		/**************************************************************************************
		     Types
		 **************************************************************************************/
		
		enum class BUTTON : unsigned {
			A = 1 << 0,
			B = 1 << 1,
			C = 1 << 2,
			D = 1 << 3,
			E = 1 << 4
		};

		/**************************************************************************************
		     Lifecycle
		 **************************************************************************************/
		
		InputManager();
		InputManager(InputManager&& other) = delete; // move initialization
		InputManager(const InputManager& other) = delete; // copy initialization
		InputManager& operator= (InputManager&& other) = delete; // move assignment
		InputManager& operator= (const InputManager& other) = delete; // copy assignment
		~InputManager();
		
		/**************************************************************************************
		     Public
		 **************************************************************************************/

		bool buttonDown(BUTTON button);
		bool buttonPressed(BUTTON button);
		std::set<BUTTON> buttonsDown();
		std::set<BUTTON> buttonsPressed();
		void shutdown();
		
		// private:
		
		/**************************************************************************************
		     Private
		 **************************************************************************************/
		
		void updateLoop();

		std::mutex				m_mtx;
		std::thread				m_updateThread;
		bool					m_stop;
		std::set<BUTTON>		m_buttonsDown;
		std::set<BUTTON>		m_buttonsPressed;
		std::set<BUTTON>		m_buttonsPressedCleared;
	};
}


#endif /* InputManager_h */
