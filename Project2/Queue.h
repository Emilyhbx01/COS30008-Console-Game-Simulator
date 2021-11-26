#pragma once

template <class T> class SinglyLinkedList;
class Livestock;
class GroupADT;
template <class T> class SingleNode;

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
