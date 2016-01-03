#include <iostream>
#include <deque>
#include <pthread.h>

enum ID{NEW_MESSAGE = 0, NO_NEW_MESSAGE = 1};

class MsgQueue;


//Define message class
class Message {

public:
	virtual ~Message(){};	//Declaration of virtual destructor with empty implementation.

};

//Declare the class/struct ReqMsg as a child of the class Message
//Since there is no need for private members of the class, it is just declared as a struct. 
//The only difference between a struct and a class in C++ is that all members of a struct is declared as public by default.
struct eventMsg: public Message {
	eventMsg(int eventID = 0): eventID_(eventID){};	//The variable carID_ is initialized to cadID before the contructor is run.
	int eventID_;
};

//Declare a struct to handle message id and message pointer
struct item {

	ID senderID_;
	eventMsg* msg_;
};


class MsgQueue {

public:
	MsgQueue(int MaxSize = 100); //Class constructor, takes queue max size as argument.
	~MsgQueue();
	void send(ID id, eventMsg* msg = NULL);	//Function to send messages, taking sender id and message pointer as arguments.
	eventMsg* receive(ID &id);	//Receive function, returns a message pointer, takes id reference as argument.

private:
	std::deque<item>* mq;	//STL container double ended queue is used.
	int maxSize, numMsg;
	pthread_mutex_t editMutex;
	pthread_cond_t notFull, notEmpty;
};
