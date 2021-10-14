#include "Stack.h"

Stack::~Stack()
{
	delete[] bookArr;
}



Stack::Stack(int sizeStack)
{
	bookArr = new Book[sizeStack];
	size = sizeStack;
	topIndex = -1;

}


bool Stack::isFull()
{
	return topIndex == size - 1;
}

void Stack::push(Book* book)
{
	if (!isFull())
	{
		topIndex++;
		bookArr[topIndex] = *book;
	}
}

void Stack::pop()
{
	if (topIndex >= 0)
	{
		topIndex--;
	}

}

Book* Stack::peek()
{
	Book* book = &bookArr[topIndex];
	cout << endl << "Title:" << (*book).getTitle() << endl;
	cout << "Description:" << (*book).getDescription() << endl;
	return book;
}

bool Stack::isEmpty()
{
	return topIndex == -1;
}