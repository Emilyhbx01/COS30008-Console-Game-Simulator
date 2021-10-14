#pragma once
#include "Item.h"


class SingleNode {

	public:

		Item item;
		SingleNode* next;
		static SingleNode NIL;
		SingleNode();
		SingleNode(Item itemValue, SingleNode* nextNode);
		SingleNode(Item itemValue);


};