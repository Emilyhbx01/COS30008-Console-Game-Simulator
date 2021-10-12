#pragma once

#include <iostream>
using namespace std;
#include "Item.h"

class IteratorBase
{
	protected:
		int index;
		int size;

	public:
		IteratorBase(int indexNo, int arrSize);
		virtual int getIndex(string item);
		virtual Item operator[](int index);
		virtual void removeElement(int itemIndex);
		virtual void addElement(Item item);
};
