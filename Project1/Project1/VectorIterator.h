#pragma once
#include "IteratorBase.h"
#include <vector>

class VectorIterator:public IteratorBase
{
	private:
		vector<Item> vectorElements;

	public:
		VectorIterator(int indexNo, int arrSize,vector<Item> vec);
		int getIndex(string item);
		bool end(int i);
		Item operator[](int index);
		void removeElement(int itemIndex);
		void addElement(Item item);
		friend ostream& operator<<(ostream& outputStream, VectorIterator*& itr);
		bool full();
};
