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
	pthread_join(t2, NULL);

	return 0;
}


void* t1_func(void* _arg) {

	//Message to t2
	char message[] = {"Hello"};

	ID tID = *(ID*)_arg;	//(int*) casts the void pointer to an integer pointer, the '*' then returns the value og the integer pointer.

	cout << "Hello from thread: " << endl;
	cout << tID << endl;

	eventMsg sentMsg;

	sentMsg.eventID_ = NEW_MESSAGE;

	cout << "Message sent from thread 1" << endl;
	handlerMq.send(tID, &sentMsg);



};

void* t2_func(void* _arg) {

	int tID = *(int*)_arg;

	cout << "Hello from thread: " << endl;
	cout << tID << endl;

	eventMsg recvMsg;

	ID eventID;

	while(1)
	{
		cout << "Thread 2 waiting for message" << endl;
		recvMsg = *handlerMq.receive(eventID);
		cout << "Event ID: " << eventID << endl;
		if(eventID == NEW_MESSAGE)
		{
			cout << "New message read from queue" << endl;
		}

	}

};



