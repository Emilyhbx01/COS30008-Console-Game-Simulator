#pragma once
#include <iostream>
using namespace std;

class Note
{
	private:
		string title;
		string message;

	public:
		Note(string noteTitle, string noteMessage);
		string getTitle();
		string getMessage();
};