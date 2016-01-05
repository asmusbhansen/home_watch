#include <iostream>
#include <unistd.h>
#include "msgqueue.hpp"
#include "temp_sensor.hpp"


using namespace std;

void * t1_func(void*);
void * t2_func(void*);

MsgQueue tSensorMq(10);
tempSensor tSensor("tSensor");



int main(int argc, char **argv) {

	pthread_t t1, t2;
	int tID[2] = {1, 2};

	if( 0 > pthread_create(&t1, NULL, &t1_func, (void*)&tID[0]))
	{
		cout << "Thread 1 creation failed" << endl;
		while(1);
	}
	if( 0 > pthread_create(&t2, NULL, &t2_func, (void*)&tID[1]))
	{
		cout << "Thread 2 creation failed" << endl;
		while(1);
	}

	//Waits for the treads to join.
	pthread_join(t1, NULL);
	cout << "Thread 1 done" << endl;
	pthread_join(t2, NULL);
	cout << "Thread 2 done" << endl;
	return 0;
}


void* t1_func(void* _arg) {

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

	cout << "Thread 1 has read the temperature sensor" << endl;
	tSensorMq.send(&sentMsg);

	usleep(1000000);
	}

};

void* t2_func(void* _arg) {

	PROCESS_ID pID = *(PROCESS_ID*)_arg;

	cout << "Hello from thread: " << endl;
	cout << pID << endl;

	Message recvMsg;

	EVENT_ID eventID;
	PROCESS_ID senderID;

	while(1)
	{
	recvMsg = tSensorMq.receive();
	eventID = recvMsg.eventID_;
	senderID = recvMsg.senderID_;
	cout << "Message received from process: " << senderID << endl;
	if(eventID == 1)
	{
		cout << "New temp reading in log: " << tSensor.readFromLog() << " degrees celcius" << endl;
	}
	}

};



