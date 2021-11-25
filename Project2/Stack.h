#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "Note.h"

 class Stack
{
private:
	vector<Note> data;
	int topIndex;

public:
	Stack(vector<Note> stackData);
	void pop();
	void push(Note note);
	bool peek();
};