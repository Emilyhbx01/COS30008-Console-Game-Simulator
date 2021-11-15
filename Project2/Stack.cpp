#include "Stack.h"

Stack::Stack(vector<Note> stackData)
{
	data = stackData;
	if (stackData.size() > 0) 
	{
		topIndex = stackData.size() - 1;
	}
	else 
	{
		topIndex = -1;
	}
	
}

void Stack::pop()
{
	data.erase(data.begin() + topIndex);
	topIndex--;
}

void Stack::push(Note note)
{
	topIndex++;
	data.push_back(note);
}

Note Stack::peek()
{
	return data[topIndex];
}
