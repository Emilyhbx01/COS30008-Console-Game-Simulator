#include "Note.h"

Note::Note(string noteTitle, string noteMessage) 
{
	title = noteTitle;
	message = noteMessage;
}

string Note::getTitle() 
{
	return title;
}
string Note::getMessage() 
{
	return message;
}