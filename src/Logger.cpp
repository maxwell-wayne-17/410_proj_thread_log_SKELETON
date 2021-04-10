/*
 * Logger.cpp
 *
 *  Created on: Mar 29, 2021
 *      Author: keith
 */
#include <iostream>
#include "../includes/Logger.h"
#include "../includes/constants.h"
using namespace std;

Logger::Logger(LOG_TYPE lt, string fn){
	Logger::lt = lt;
	Logger::fn = fn;
	//open file if lt is for files
	if (lt == LOG_FILE){
		Logger::fs = ofstream(fn);
	}
}

void Logger::Log(string info){

	if (lt == LOG_CONSOLE){
		lock_guard<mutex> lock(mtx);
		cout << info << endl;
	}
	else{ //LOG_FILE
		lock_guard<mutex> lock(mtx);
		fs << info << endl;
	}


}

Logger::~Logger(){
	//Unlock just in case
	mtx.unlock();
	// Close file
	if ( fs.is_open() ){
		fs.close();
	}
}

