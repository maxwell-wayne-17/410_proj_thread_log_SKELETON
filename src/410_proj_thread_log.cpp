//============================================================================
// Name        : 410_proj_thread_log.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <thread>
#include <iostream>
#include <vector>
#include "../includes/constants.h"
#include "../includes/Logger.h"

using namespace std;

//NOTE: you should have no mutexes in this file
//TODO linker errors?  Did you include the pthread library?   And set the proper dialect?  Set
//TODO declare globals, one for file one for console
Logger fileLogger(LOG_FILE);
Logger consoleLogger(LOG_CONSOLE);
// Boolean to stop doing work once program is done sleeping
bool doWork = true;

/***
 * TODO log info to both file and console. You can do this with 2 Logger objects. 
 * 		Note:  These logger objects cannot be local variables, they must be shared 
 * 		amongst the threads. (why?) - Otherwise there will be no concurrency
 * TODO this function should run until main (or another thread) asks it to quit
 * @param info  to log
 * returns void
 */
void fun(string info){

	// Allows main to ask threads to stop doing work
	while (doWork){
		fileLogger.Log(info);
		consoleLogger.Log(info);
	}


}
int main() {
	
	//TODO start as many threads as you have cores (see std::thread::hardware_concurrency())
	//TODO save these threads in a vector
	std::vector<std::thread> vecThreads;
	int numThreads = std::thread::hardware_concurrency();

	std::string input = "a";
	for (int i=0; i < numThreads/2; i++){
		//Simple way to differentiate the input string for the threads
		input.append("a");
		vecThreads.push_back( std::thread( fun, input ) );
	}

	//TODO let threads run a bit (5 seconds)
	this_thread::sleep_for(chrono::milliseconds(5000));
	
	//TODO ask them all to stop
	doWork = false;

	//TODO wait for all threads to finish
	for (auto& t : vecThreads){
		t.join();
	}
	
	return 0;
}
