#pragma once
#include <iostream>
using namespace std;
#include "VectorIterator.h"
#include <string>
#include "ArrayIterator.h"
#include "SinglyLinkedList.h"
#include "Stack.h"
#include "NoteStruct.h"

class Player
{
	private:

		VectorIterator* bagpack;
		SinglyLinkedList* droppedItemList;
		int energy;
		string location;
		Note* note;

	public:
	
		~Player();
		Player();
		string getLocation();
		void setLocation(string playerLocation);
		int getEnergy();
		void setEnergy(int energyLvl);
		bool addToBagpack(Item item, ArrayIterator*& itemItr);
		Item removeFromBagpack(string itemName);
		void grabItem(ArrayIterator*& itemItr);
		void dropItem(ArrayIterator*& itemItr);
		void seeDroppedItems();
		vector<Item> splitItems(string items, ArrayIterator*& itemItr);
		vector<Item> splitItems(string items);
		void walk(vector<string> locations);
		void seeBook(Stack* books);
		void readBook(Stack* books);
		void takeNote();
		void viewNote();
		void callHelp(bool& callHelp);
		void signalForHelp(bool& win);
		void consumeFood();

};