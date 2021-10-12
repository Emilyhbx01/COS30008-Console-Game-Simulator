#include "VectorIterator.h"



VectorIterator::VectorIterator(int indexNo, int arrSize, vector<Item> vec) :IteratorBase(indexNo, arrSize) 
{
	vectorElements = vec;
}


int VectorIterator::getIndex(string item) 
{
	for (int i = 0; i < size; i++) 
	{
		if (vectorElements[i].getName() == item) 
		{
			return i;
		}
	}

	return -1;
}



bool VectorIterator::full() 
{
	if (vectorElements.size() == size) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

void VectorIterator::removeElement(int itemIndex) 
{

	vectorElements.erase(vectorElements.begin()+itemIndex);
}

void VectorIterator::addElement(Item item) 
{
	if (vectorElements.size() < size) 
	{
		vectorElements.push_back(item);
	}
	
}

Item VectorIterator::operator[](int index)
{

	return vectorElements.at(index);
}

ostream& operator<<(ostream& outputStream, VectorIterator*& itr) 
{
	for (int i = 0; i < itr->vectorElements.size(); i++) 
	{
		if (i != itr->vectorElements.size() - 1) 
		{
			outputStream << itr->vectorElements[i].getName() << ",";
		}
		else 
		{
			outputStream << itr->vectorElements[i].getName();
		}
		
	}
	return outputStream;
}