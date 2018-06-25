//
//  main.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/14/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//

#include <iostream>
#include <signal.h>
#include <memory>

#include "TacoMonitor.h"


using namespace std;
using namespace tacomon;


unique_ptr<TacoMonitor> tacoMonitor;


void signalHandler(int signum) {
	
	cout << "Caught signal: " << signum << endl;
	tacoMonitor->stop();
}

int main(int argc, const char* argv[]) {
	
	auto args = vector<string>();
	for (int i=0; i<argc; ++i) {
		args.push_back(argv[i]);
	}
	
	signal(SIGABRT, signalHandler);
	signal(SIGINT, signalHandler);
	
	tacoMonitor = make_unique<TacoMonitor>();
	
	return tacoMonitor->start(args);
}
