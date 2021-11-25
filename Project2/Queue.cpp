
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
		struct tm gmTime;
		gmtime_s(&gmTime,&timePlanted);
		
		cout << "Name:" << temp->data.getItem().getName() << endl;
		cout << "Time planted:" << gmTime.tm_hour << ":" << gmTime.tm_min << ":" << gmTime.tm_sec << endl;
		gmtime_s(&gmTime,&timeToHarvest);
		cout << "Time to harvest:" << gmTime.tm_hour << ":" << gmTime.tm_min << ":" << gmTime.tm_sec << endl;
		temp = linkedList->getHead()->next;
	}
}

void Queue::readyForHarvest(GroupADT& notifications) 
{
	if (!linkedList->isEmpty()) 
	{
		Livestock livestock = linkedList->getHead()->data;
		if (livestock.canHarvest())
		{
			if (livestock.getItem().getType() == "plant")
			{
				vector<Livestock> plantations = notifications.getPlantations();
				plantations.push_back(livestock);
				notifications.setPlantations(plantations);
			}
			else
			{
				vector<Livestock> animalsReared = notifications.getAnimalsReared();
				animalsReared.push_back(livestock);
				notifications.setAnimalsReared(animalsReared);
			}
			dequeue();
			readyForHarvest(notifications);
		}
	}
	
}