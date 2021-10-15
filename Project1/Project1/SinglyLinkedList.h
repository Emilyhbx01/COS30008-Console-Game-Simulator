
#pragma once
#include "SingleNode.h"

class SinglyLinkedList
{
	
	private:
		
		SingleNode* head;
		SingleNode* tail;
		int maxSize;

	public:
		~SinglyLinkedList();
		SinglyLinkedList(int size);

		void append(SingleNode* itemNode);

		void remove(Item item);

		void showContent();

		int getListSize();


};