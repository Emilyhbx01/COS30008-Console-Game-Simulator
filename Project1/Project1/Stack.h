#pragma once
#include <iostream>
using namespace std;
#include "Book.h"

class Stack 
{
	private:
		Book* bookArr;
		int topIndex;
		int size;

	public:
		~Stack();
		Stack(int sizeStack);
		bool isFull();
		void push(Book* book);
		void pop();
		Book* peek();
		bool isEmpty();
};

