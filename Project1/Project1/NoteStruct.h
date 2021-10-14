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
	void append(string content) 
	{
		noteContent = noteContent + "\n" + content;
	}
	void view() 
	{
		cout << noteContent << endl;
	}

};