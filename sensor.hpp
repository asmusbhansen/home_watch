//The sensor class is a parent class for all other sensors
#include <string>
#include <fstream>
#include <stdio.h>
#include <iostream>

using namespace std;

class Sensor {

public:

	Sensor(string name): sensorName_(name){
	//Constructor removes the old logfile
	logFileName_ = sensorName_ + "_log" ;

	dataEntries_ = 0;
	/*
	if( remove( logFileName_.c_str ) != 0 )
		cout << "Error deleting file" << endl;
	else
		cout << "File successfully deleted" << endl;
	*/
	};

	virtual ~Sensor(){};	//The destructor is declared private such that derived objects will have their own destructor called when deleted.

	//Read and write methods
	int writeToLog(string data)
	{
		ofstream logFile;
		logFile.open(logFileName_.c_str(), ofstream::out | ofstream::app);	//Open file for writing to bottom. 
		if(!logFile)
		{
			return -1;
		}

		logFile << data << endl;
		dataEntries_++;
		logFile.close();

		return 0;
	}
	string readFromLog(){

		string tempData;
		ifstream logFile;
		logFile.open(logFileName_.c_str());
		for(int i = 0; i < dataEntries_; i++)
		{
			getline(logFile, tempData);	//This reads the last line of the log file
		}
		logFile.close();

		return tempData;
	}

private:

	string sensorName_;
	int dataEntries_;
	string logFileName_;
};
