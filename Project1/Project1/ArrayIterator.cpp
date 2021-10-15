#include "ArrayIterator.h"


ArrayIterator::~ArrayIterator() 
{
	
	delete[] itemArray;
}

ArrayIterator::ArrayIterator(Item* arr, int indexNo, int arrSize) :IteratorBase(indexNo, arrSize)
{
	itemArray = arr;
}


int ArrayIterator::getIndex(string item)
{
	for (int i = 0; i < size; i++)
	{
		if (item == itemArray[i].getName())
		{
			return i;
		}
	}

	return -1;
}

//remove element by copying the elements into a new array except for the element to be removed
void ArrayIterator::removeElement(int itemIndex)
{
	for (int i = 0; i < size; i++)
	{
		if (i == itemIndex)
		{
			Item* newItemArray = new Item[size - 1];
			copy(itemArray, itemArray + i, newItemArray);
			copy(itemArray + i + 1, itemArray + size, newItemArray + i);
			delete[] itemArray;
			itemArray = newItemArray;
			--size;
		}
	}
}

//add new elements into the array by creating a new dynamic array of a bigger size
//copy the old elements to the new array and add the new element at the last of the array
void ArrayIterator::addElement(Item item)
{
	int newSize = size + 1;
	Item* newItemArray = new Item[size + 1];
	copy(itemArray, itemArray + size, newItemArray);
	newItemArray[newSize - 1] = item;
	delete[] itemArray;
	itemArray = newItemArray;
	++size;
}


Item ArrayIterator::operator[](int index) 
{
	return itemArray[index];
}

void ArrayIterator::displayItems(string playerLocation)
{
	int count = 0;

	for (int i = 0; i < size; i++)
	{
		Item item = itemArray[i];
		if (item.getLocation() == playerLocation) 
		{
			count++;
			if (count == 1) 
			{
				cout << endl << "There are " << endl;
			}

			cout << "-" << item.getName() << endl;
		}
		
	}
	if (count == 0)
	{
		cout << endl << "There is nothing around you" << endl;
	
	}
}