//
//  main.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/14/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//


#include "TacoMonitor.h"


using namespace std;
using namespace tacomon;


//void signalHandler(int signum) {
////	cout << "Interrupt signal (" << signum << ") received.\n";
//	
//	// cleanup and close up stuff here  
//	// terminate program
//	
//	exit(signum);  
//}

int main(int argc, const char* argv[]) {
	
	auto args = vector<string>();
	for (int i=0; i<argc; ++i) {
		args.push_back(argv[i]);
	}
	
	//signal(SIGINT, signalHandler);
	
	return TacoMonitor().start(args);
}
