#include "Stack.h"
#include "Note.h"

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
	if (topIndex >= 0) 
	{
		data.erase(data.begin() + topIndex);
		topIndex--;
	}
	
}

void Stack::push(Note note)
{
	topIndex++;
	data.push_back(note);
}

bool Stack::peek()
{
	if (topIndex >= 0) 
	{
		Note note = data[topIndex];
		cout << note.getTitle() << endl;
		cout << note.getMessage() << endl;
		return true;
	}
	return false;
}
