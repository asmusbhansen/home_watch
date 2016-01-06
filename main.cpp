#include <iostream>
#include <unistd.h>
#include "msgqueue.hpp"
#include "temp_sensor.hpp"
#include "page_generator.hpp"

using namespace std;

void * tempReaderThreadFunction(void*);
void * pageUpdaterThreadFunction(void*);

MsgQueue pageUpdaterMq(10);
tempSensor tSensor("tSensor");



int main(int argc, char **argv) {

	pthread_t tempReaderThread, pageUpdaterThread;
	int tID[2] = {1, 2};

	if( 0 > pthread_create(&tempReaderThread, NULL, &tempReaderThreadFunction, (void*)&tID[0]))
	{
		cout << "Thread 1 creation failed" << endl;
		while(1);
	}
	if( 0 > pthread_create(&pageUpdaterThread, NULL, &pageUpdaterThreadFunction, (void*)&tID[1]))
	{
		cout << "Thread 2 creation failed" << endl;
		while(1);
	}

	while(1);
}


void* tempReaderThreadFunction(void* _arg) {

	//initialize temperature sensor
	tSensor.initSensor();

	PROCESS_ID pID = *(PROCESS_ID*)_arg;	//(int*) casts the void pointer to an integer pointer, the '*' then returns the value og the integer pointer.

	cout << "Hello from thread: " << endl;
	cout << pID << endl;

	while(1)
	{

	tSensor.readSensor();

	Message sentMsg;

	sentMsg.eventID_ = NEW_TEMP_READING;
	sentMsg.senderID_ = pID;

	//cout << "Thread 1 has read the temperature sensor" << endl;
	pageUpdaterMq.send(&sentMsg);

	usleep(1000000);
	}

};

void* pageUpdaterThreadFunction(void* _arg) {

	PROCESS_ID pID = *(PROCESS_ID*)_arg;

	cout << "Hello from thread: " << endl;
	cout << pID << endl;

	Message recvMsg;

	EVENT_ID eventID;
	PROCESS_ID senderID;

	while(1)
	{
	recvMsg = pageUpdaterMq.receive();
	eventID = recvMsg.eventID_;
	senderID = recvMsg.senderID_;
	//cout << "Message received from process: " << senderID << endl;
	string temperatureReading = tSensor.readFromLog();
	if(eventID == 1)
	{
		cout << "New temp reading in log: " << temperatureReading << " degrees celcius" << endl;
	}

	pageGenerator(temperatureReading);
	cout << "Reading written to homepage" << endl;
	}

};



