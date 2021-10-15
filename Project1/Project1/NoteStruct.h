#pragma once

#include <iostream>
using namespace std;

struct Note
{
	string noteContent;
	Note() 
	{
		noteContent = "";
	}

	//when the player adds new note, the note will be appended behind the old note
	void append(string content) 
	{
		noteContent = noteContent + "\n" + content;
	}

	//displays all the notes written
	void view() 
	{
		cout << noteContent << endl;
	}

};