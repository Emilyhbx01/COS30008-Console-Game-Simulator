#define _CRT_SECURE_NO_WARNINGS
#include "Queue.h"

Queue::~Queue()
{
	delete linkedList;
}

Queue::Queue()
{
	linkedList = new SinglyLinkedList<Livestock>();
}

void Queue::enqueue(SingleNode<Livestock>& node)
{
	linkedList->append(node);
}

void Queue::dequeue()
{
	linkedList->removeHead();
}

void Queue::displayQueue()
{
	SingleNode<Livestock>* temp = linkedList->getHead();
	while (temp != &SingleNode<Livestock>::NIL)
	{
		time_t timePlanted = temp->data.getTimePlanted();
		time_t timeToHarvest = temp->data.getTimeToHarvest();
		tm* localTime = gmtime(&timePlanted);

		cout << "Name:" << temp->data.getItem().getName() << endl;
		cout << "Time planted:" << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << endl;
		localTime = gmtime(&timeToHarvest);
		cout << "Time to harvest:" << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << endl;
		temp = linkedList->getHead()->next;
	}
}