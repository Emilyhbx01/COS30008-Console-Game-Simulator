#include "DoublyLinkedList.h"

DoublyLinkedList::~DoublyLinkedList()
{
	while (head != &DoubleNode::NIL)
	{
		DoubleNode* temp = head->next;
		delete head;
		head = temp;
	}
}

DoublyLinkedList::DoublyLinkedList()
{
	head = &DoubleNode::NIL;
	tail = &DoubleNode::NIL;
	current = &DoubleNode::NIL;
}

DoublyLinkedList::DoublyLinkedList(DoubleNode* headNode, DoubleNode* tailNode)
{
	head = headNode;
	tail = tailNode;
	current = headNode;
}

void DoublyLinkedList::append(DoubleNode* itemNode)
{
	//the new node will always be appended to the end whereby the tail is always NIL 
	itemNode->next = tail->next;
	itemNode->prev = tail;
	tail->next = itemNode;
	tail = itemNode;
}


void DoublyLinkedList::showContent()
{
	if (current != &DoubleNode::NIL)
	{
		cout << current->content << endl;
	}
}

void DoublyLinkedList::next()
{
	if ((current->next) != &DoubleNode::NIL)
	{
		current = current->next;
	}

}

void DoublyLinkedList::previous()
{
	if ((current->prev) != &DoubleNode::NIL)
	{
		current = current->prev;
	}

}