#pragma once
#include "SinglyLinkedList.h"
#include "Livestock.h"
#include "GroupADT.h"

class Queue 
{
	public:
		SinglyLinkedList<Livestock>* linkedList;
		~Queue();
		Queue();
		void enqueue(SingleNode<Livestock>& node);
		void dequeue();
		void displayQueue();
		void readyForHarvest(GroupADT& notifications);
};
