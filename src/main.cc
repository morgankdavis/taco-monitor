//
//  main.cc
//	taco-monitor
//
//  Created by Morgan Davis on 6/14/18.
//  Copyright © 2018 Morgan K Davis. All rights reserved.
//

#include <execinfo.h>
#include <iostream>
#include <signal.h>
#include <memory>

#include "TacoMonitor.h"


using namespace std;
using namespace tacomon;


unique_ptr<TacoMonitor> tacoMonitor;


static void saveStackTrace(int signum) {
	
	static const unsigned MAX_FRAMES = 64;
	static const char* LOG_PATH = "/var/log/taco_mon.log";
	
	FILE* out = fopen(LOG_PATH, "w");
	if (out != NULL) {
		
//		/* print some text */
//		const char *text = "Write this to the file";
//		fprintf(out, "Some text: %s\n", text);
//		
//		/* print integers and floats */
//		int i = 1;
//		float py = 3.1415927;
//		fprintf(out, "Integer: %d, float: %f\n", i, py);
//		
//		/* printing single chatacters */
//		char c = 'A';
//		fprintf(out, "A character: %c\n", c);
//		
//		fclose(out);
		
		
		// get the date/time string
		time_t rawtime;
		struct tm* timeinfo;
		char dateStr[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(dateStr, sizeof(dateStr), "%c", timeinfo);
		
		fprintf(out, "\n--- SIGNAL %d %s ---\n\n", signum, dateStr);
		printf("Writing stack trace to %s...\n", LOG_PATH);

		// get and save the stack trace
		void* addrList[MAX_FRAMES];
		unsigned addrLen = backtrace(addrList, sizeof(addrList) / sizeof(void*));
		printf("addrLen: %d\n", addrLen);
		if (addrLen != 0) {
			
			char** symbolList = backtrace_symbols(addrList, addrLen);
			for (int i=0; i<addrLen; ++i) {
				printf("i: %d\n", i);
				fprintf(out, "%s\n", symbolList[i]);
			}
			
			free(symbolList);
			fclose(out);
		}
		else {
			printf("No stack trace");
			fprintf(out, "No stack trace.\n");
			fclose(out);
		}
	}
	else {
		printf("Error opening log file.\n");
	}
}

void signalHandler(int signum) {
	
	cout << "Caught signal: " << signum << endl;
	switch (signum) {
		case SIGTERM:
		case SIGABRT:
		case SIGINT:
			tacoMonitor->stop();
		break;
		case SIGSEGV:
		case SIGILL:
		case SIGFPE:
		default:
			saveStackTrace(signum);
	}
	
	exit(signum);
}

int main(int argc, const char* argv[]) {
	
	auto args = vector<string>();
	for (int i=0; i<argc; ++i) {
		args.push_back(argv[i]);
	}
	
	// termination
	signal(SIGTERM, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGINT, signalHandler);
	// errors
	signal(SIGSEGV, signalHandler );
	signal(SIGILL, signalHandler );
	signal(SIGFPE, signalHandler );
	
	tacoMonitor = make_unique<TacoMonitor>();
	
	return tacoMonitor->start(args);
}
