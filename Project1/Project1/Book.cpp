#include "Book.h"

Book::~Book()
{
	delete pageContent;
}

Book::Book()
{
	title = "";
	description = "";
	pageContent = new DoublyLinkedList();
}

Book::Book(string bookTitle, string bookDescription, DoublyLinkedList* page)
{
	title = bookTitle;
	description = bookDescription;
	pageContent = page;
}

string Book::getTitle()
{
	return title;
}

string Book::getDescription()
{
	return description;
}

DoublyLinkedList* Book::getContent()
{
	return pageContent;
}