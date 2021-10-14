#pragma once
#include <iostream>
using namespace std;

class DoubleNode 
{
	public:
		string content;
		DoubleNode* next;
		DoubleNode* prev;
		static DoubleNode NIL;

		DoubleNode();
		DoubleNode(string contentNode);
};
