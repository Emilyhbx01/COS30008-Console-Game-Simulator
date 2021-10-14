#pragma once

#include <iostream>
using namespace std;
#include "DoublyLinkedList.h"

class Book
{
	private:
		string title;
		string description;
		DoublyLinkedList* pageContent;

	public:
		~Book();

		Book();

		Book(string bookTitle, string bookDescription, DoublyLinkedList* page);

		string getTitle();

		string getDescription();

		DoublyLinkedList* getContent();
};
