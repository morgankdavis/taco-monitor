//
//  Beeper.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/25/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "Beeper.h"

#include <iostream>
#include <wiringPi.h>


// we want a signal pin that is HIGH on boot, so the buzzer does not sound.
// https://raspberrypi.stackexchange.com/questions/51479/gpio-pin-states-on-powerup?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
//	"The power on state is defined in BCM2835 ARM Peripherals page 102.
//
//	Basically all GPIO pins are in INPUT mode, GPIO 0-8 have pull-ups to 3V3 enabled, GPIO 9-27 have pull-downs to 0V enabled."

#define BUZZER_BCM_PIN		6
//#define BUZZER_PERIOD		1000


using namespace std;
using namespace tacomon;


/**************************************************************************************
     Static Prototypes
 **************************************************************************************/

static void SetupGPIO();

/**************************************************************************************
     Lifecycle
 **************************************************************************************/

Beeper::Beeper():
	m_beeping(false) {
	
	SetupGPIO();
}

Beeper::~Beeper() {
	
}

/**************************************************************************************
     Public
 **************************************************************************************/

void Beeper::on() {
	
	digitalWrite(BUZZER_BCM_PIN, LOW);
}

void Beeper::off() {
	
	digitalWrite(BUZZER_BCM_PIN, HIGH);
}

bool Beeper::beeping() const {
	
	return m_beeping;
}

/**************************************************************************************
     Private
 **************************************************************************************/

/**************************************************************************************
     Static
 **************************************************************************************/

void SetupGPIO() {
	
	cout << "Setting up GPIO..." << endl;
	
	wiringPiSetupGpio(); // use BCM pin numbers
	// http://wiringpi.com/reference/
	pinMode(BUZZER_BCM_PIN, OUTPUT);
	digitalWrite(BUZZER_BCM_PIN, HIGH); // high == off
}
