#include "Queue.h"
#include "SinglyLinkedList.h"
#include "Livestock.h"
#include "GroupADT.h"

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
	bool isEmpty = true;
	SingleNode<Livestock>* temp = linkedList->getHead();
	while (temp != &SingleNode<Livestock>::NIL)
	{
		isEmpty = false;
		time_t timePlanted = temp->data.getTimePlanted();
		time_t timeToHarvest = temp->data.getTimeToHarvest();
		struct tm localTime;
		localtime_s(&localTime,&timePlanted);
		
		cout << "Name:" << temp->data.getItem().getName() << endl;
		cout << "Quantity:"<< temp->data.getItem().getQuantity() << endl;
		cout << "Time planted:" << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec << endl;
		localtime_s(&localTime,&timeToHarvest);
		cout << "Time to harvest:" << localTime.tm_hour << ":" << localTime.tm_min << ":" << localTime.tm_sec << endl << endl;
		temp = temp->next;
	}

	if (isEmpty) 
	{
		cout << "None" << endl;
	}
}

//checks if each plant or animals in the queue is ready for harvest
void Queue::readyForHarvest(GroupADT& notifications) 
{
	if (!linkedList->isEmpty()) 
	{
		//get the head in the queue first because the first item to be planted/reared will be the first to be ready for harvest
		Livestock livestock = linkedList->getHead()->data;
		if (livestock.canHarvest())
		{
			//when the plant/animal is ready for harvest, it will be removed from the queue and added to the notifications 
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