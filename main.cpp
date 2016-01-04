#include <iostream>
#include "msgqueue.hpp"

using namespace std;

void * t1_func(void*);
void * t2_func(void*);

MsgQueue handlerMq(10);

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

	PROCESS_ID pID = *(PROCESS_ID*)_arg;	//(int*) casts the void pointer to an integer pointer, the '*' then returns the value og the integer pointer.

	cout << "Hello from thread: " << endl;
	cout << pID << endl;

	Message sentMsg;

	sentMsg.eventID_ = NEW_MESSAGE;
	sentMsg.senderID_ = pID;

	cout << "Message sent from thread 1" << endl;
	handlerMq.send(&sentMsg);

};

void* t2_func(void* _arg) {

	PROCESS_ID pID = *(PROCESS_ID*)_arg;

	cout << "Hello from thread: " << endl;
	cout << pID << endl;

	Message recvMsg;

	EVENT_ID eventID;
	PROCESS_ID senderID;
	while(eventID != 1)
	{

	recvMsg = handlerMq.receive();
	eventID = recvMsg.eventID_;
	senderID = recvMsg.senderID_;
	cout << "Message received from process: " << senderID << endl;
	cout << "Message is: " << eventID << endl;

	}

};



