#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "Item.h"
#include "Livestock.h"
#include "Queue.h"
#include "Stack.h"

int main() 
{
	/*
	Item item("Chicken", 10.5, 20, 10, "Rearing chicken....", 180);
	Livestock livestock(item);
	SingleNode<Livestock>* node1 = new SingleNode<Livestock>(livestock);

	Queue* plantations = new Queue();
	plantations->enqueue(*node1);
	plantations->displayQueue();
	delete plantations;
	*/

	/*
	vector<Note> notesVector = { Note("Best seed to plant","Corn, wheat"),Note("Best animal to rear","Chickens") };
	Stack* notes = new Stack(notesVector);
	notes->pop();
	cout << notes->peek().getTitle();
	*/

	return 0;
}