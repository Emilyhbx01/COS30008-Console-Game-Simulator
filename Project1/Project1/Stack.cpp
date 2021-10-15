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

//add new element to the top of the stack
void Stack::push(Book* book)
{
	if (!isFull())
	{
		topIndex++;
		bookArr[topIndex] = *book;
	}
}

//remove the element at the top of the stack
void Stack::pop()
{
	if (topIndex >= 0)
	{
		topIndex--;
	}

}

//return the current element at the top of the stack
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