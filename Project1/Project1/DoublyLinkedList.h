#pragma once
#include "DoubleNode.h"


class DoublyLinkedList 
{

	private:
		DoubleNode* head;
		DoubleNode* tail;
		DoubleNode* current;

	public:
		~DoublyLinkedList();
		DoublyLinkedList();
		DoublyLinkedList(DoubleNode* headNode, DoubleNode* tailNode);
		void append(DoubleNode* itemNode);
		void showContent();
		void next();
		void previous();
	
};