#pragma once
#include "IteratorBase.h"

class ArrayIterator : public IteratorBase
{
	private:
		Item* itemArray;


	public:
		~ArrayIterator();
		ArrayIterator(Item* arr, int indexNo, int arrSize);
		int getIndex(string item);
		void removeElement(int itemIndex);
		void addElement(Item item);
		Item operator[](int index);
		void displayItems(string playerLocation);
	

};