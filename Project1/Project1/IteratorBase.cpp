#include "IteratorBase.h"

IteratorBase::IteratorBase(int indexNo, int arrSize)
{
	index = indexNo;
	size = arrSize;
}


int IteratorBase::getIndex(string item)
{
	return -1;
}


Item IteratorBase::operator[](int index) 
{
	return Item();
}

void IteratorBase::removeElement(int itemIndex) 
{

}

void IteratorBase::addElement(Item item) 
{
	
}