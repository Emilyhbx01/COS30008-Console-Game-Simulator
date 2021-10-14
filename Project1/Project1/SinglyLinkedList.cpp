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
			if (node == head)
			{
				head = node->next;
			}
			else if (node == tail)
			{
				tail = prev;
			}
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
		cout << "Item:" << node->item.getName() << "\t" << "Location:" << node->item.getLocation() << endl;
		node = node->next;
		count++;
	}

	if (count == 0)
	{
		cout << "No dropped items" << endl;
	}
}

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