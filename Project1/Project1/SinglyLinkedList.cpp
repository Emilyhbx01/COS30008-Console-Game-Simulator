#include "SinglyLinkedList.h"


SinglyLinkedList::~SinglyLinkedList() 
{
	while (head != &SingleNode::NIL) 
	{
		SingleNode* temp = head->next;
		delete head;
		head = temp;

	}
}


SinglyLinkedList::SinglyLinkedList(int size)
{
	head = &SingleNode::NIL;
	tail = &SingleNode::NIL;
	maxSize = size;
}

void SinglyLinkedList::append(SingleNode* itemNode)
{
	//the new node will always be appended to the end whereby the tail is always NIL 

	if (head == &SingleNode::NIL && tail == &SingleNode::NIL)
	{
		head = itemNode;
		tail = itemNode;
	}
	else
	{
		//remove the head element and assign new head if the list is full 
		if (getListSize() == maxSize && head != &SingleNode::NIL)
		{
			SingleNode* tempNode = head->next;
			delete head;
			head = tempNode;
		}

		itemNode->next = tail->next;
		tail->next = itemNode;
		tail = itemNode;
	}


}

void SinglyLinkedList::remove(Item item)
{
	SingleNode* node = head;
	SingleNode* prev = head;

	while (node != &SingleNode::NIL)
	{
		if (node->item.getName() == item.getName())
		{
			//if the node to be removed is the head, then a new head will have to be assigned
			if (node == head)
			{
				head = node->next;
			}
			//if the node to be removed is the tail, then a new tail will have to be assigned
			else if (node == tail)
			{
				tail = prev;
			}
			//if the node to be removed is the one and only node in the list, the head and tail will be NIL after removal of the node
			else if (node == tail && node == head)
			{
				head = &SingleNode::NIL;
				tail = &SingleNode::NIL;
			}
			else
			{
				prev->next = node->next;
			}

		}
		node = node->next;
	}
}


void SinglyLinkedList::showContent()
{
	SingleNode* node = head;
	int count = 0;
	while (node != &SingleNode::NIL)
	{
		cout << "Item:" << node->item.getName() << "\t\t" << "Location:" << node->item.getLocation() << endl;
		node = node->next;
		count++;
	}

	if (count == 0)
	{
		cout << "No dropped items" << endl;
	}
}

//return the total number of elements in the list
int SinglyLinkedList::getListSize()
{
	SingleNode* node = head;
	int count = 0;
	while (node != &SingleNode::NIL)
	{
		count++;
		node = node->next;
	}

	return count;
}