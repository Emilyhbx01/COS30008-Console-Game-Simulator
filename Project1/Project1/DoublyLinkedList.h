#pragma once
#include "Item.h"

struct DoubleNode{
	Item item;
	DoubleNode* next;
	DoubleNode* prev;
};

class DoublyLinkedList 
{
	public:
		DoubleNode* head;
		DoubleNode* tail;

		void append(DoubleNode* item) 
		{
			item->next = tail->next;
			tail->next = item;
			tail = item;
		}
		
	
};