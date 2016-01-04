#include <iostream>
#include <deque>
#include <pthread.h>

enum PROCESS_ID{t1 = 0, t2 = 1};
enum EVENT_ID{NO_NEW_MESSAGE = 0, NEW_MESSAGE = 1};

class MsgQueue;

/*
//Define message class
class Message {

public:
	virtual ~Message(){};	//Declaration of virtual destructor with empty implementation.

};

//Declare the class/struct ReqMsg as a child of the class Message
//Since there is no need for private members of the class, it is just declared as a struct. 
//The only difference between a struct and a class in C++ is that all members of a struct is declared as public by default.
struct eventMsg: public Message {
	EVENT_ID eventID_;
};
*/
//Declare a struct to handle message id and message pointer
struct Message {

	PROCESS_ID senderID_;	//The sender ID, is the ID of the thread/process from where the message originates.
	EVENT_ID eventID_; 	//The eventMsg struct only contains 
};


class MsgQueue {

public:
	MsgQueue(int MaxSize = 100); //Class constructor, takes queue max size as argument.
	~MsgQueue();
	void send(Message * _msg);	//Function to send messages, taking sender id and message pointer as arguments.
	Message receive();	//Receive function, returns a message pointer, takes id reference as argument.

private:
	std::deque<Message>* mq;	//STL container double ended queue is used.
	int maxSize, numMsg;
	pthread_mutex_t editMutex;
	pthread_cond_t notFull, notEmpty;
};
