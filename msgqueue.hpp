#include <iostream>
#include <deque>
#include <pthread.h>

enum PROCESS_ID{t1 = 0, t2 = 1};
enum EVENT_ID{NO_NEW_MESSAGE = 0, NEW_MESSAGE = 1};

class MsgQueue;


//Declare a struct to handle message and event ID
struct Message {

	PROCESS_ID senderID_;
	EVENT_ID eventID_;
};


class MsgQueue {

public:
	MsgQueue(int MaxSize = 100); //Class constructor, takes queue max size as argument.
	~MsgQueue();
	void send(Message * _msg);	//Function to send messages, taking message pointer as argument.
	Message receive();	//Receive function, returns the message.

private:
	std::deque<Message>* mq;	//STL container double ended queue is used.
	int maxSize, numMsg;
	pthread_mutex_t editMutex;
	pthread_cond_t notFull, notEmpty;
};
