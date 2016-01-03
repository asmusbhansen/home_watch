#include "msgqueue.hpp"

using namespace std;

MsgQueue::MsgQueue(int _maxSize) {

	pthread_mutex_init(&editMutex, NULL);
	pthread_cond_init(&notFull, NULL);
	pthread_cond_init(&notEmpty, NULL);

	mq = new std::deque<item>;
	mq -> resize(_maxSize);
	maxSize = _maxSize;
	numMsg = 0;

}

MsgQueue::~MsgQueue() {

	delete mq;	//The destructor deletes the message queue to avoid memory leak.

}

void MsgQueue::send(ID id, eventMsg* msg) {	//The send function takes an ID and message pointer as arguments.

	pthread_mutex_lock(&editMutex);	//When a process is sending a message to the message queue, only that process can edit the queue.
	cout << "Mutex locked by MsgQueue send function" << endl;
	while(numMsg == maxSize) {

		pthread_cond_wait(&notFull, &editMutex);	//If the queue is full, the process waits for signalling. Other processes can still work in the meantime.
								//The mutex is unlocked for other processes to use, and is returned when the coditional wait is over.

	}

	item tempItem;
	tempItem.senderID_ = id; //The message item is given the ID from the message to be sent.
	tempItem.msg_ = msg;	//The message from the  sender is transferred to the message item.
	mq -> push_back(tempItem);	//The message item is pushed to the message queue.
	pthread_cond_signal(&notEmpty); //Other threads are signalled that the message queue is no longer empty.
	cout << "Send function signals to waiting receive function" << endl;
	pthread_mutex_unlock(&editMutex); //The edit mutex is released before exiting the routine.
}

eventMsg * MsgQueue::receive(ID &id) {

	pthread_mutex_lock(&editMutex);

	while(numMsg == 0) {
		pthread_cond_wait(&notEmpty, &editMutex);	//Same behaviour as above.
		cout << "Thread waiting to recevie message" << endl;
	}
	cout << "Thread received message" << endl;
	item tempItem = mq->front();	//The front item of the message queue is read.

	eventMsg* tempMsg = tempItem.msg_;
	id = tempItem.senderID_;
	mq -> pop_front();	//The front item of the message queue is removed.
	numMsg--;
	pthread_cond_signal(&notFull);
	pthread_mutex_unlock(&editMutex);
	return tempMsg;

}


