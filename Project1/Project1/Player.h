#pragma once
#include <iostream>
using namespace std;
#include "VectorIterator.h"
#include <string>
#include "ArrayIterator.h"

class Player
{
private:

	VectorIterator* bagpack;
	int energy;
	string location;

public:
	
	~Player() 
	{
		delete bagpack;
	}

	Player()
	{
		bagpack = new VectorIterator(0, 3, vector<Item>{});
		energy = 100;
		location = "class";
	};



	string getLocation()
	{
		return location;
	}

	void setLocation(string playerLocation)
	{
		location = playerLocation;
	}

	void addToBagpack(Item item, ArrayIterator*& itemItr) 
	{
		if (bagpack->full()) 
		{
			dropItem(itemItr);
		}
		else 
		{
			bagpack->addElement(item);
			cout << "Added " << item.getName() << " to your bag" << endl;
			itemItr->removeElement(itemItr->getIndex(item.getName()));

		}
		
	}

	Item removeFromBagpack(string itemName) 
	{
		int index = bagpack->getIndex(itemName);
		Item item = (*bagpack)[index];
		bagpack->removeElement(index);
		return item;
		
	}


	void grabItem(ArrayIterator*& itemItr) 
	{
		string items;
		cout << "What item do you want to collect?" << endl;
		getline(cin, items);
		vector<Item> vecItems = splitItems(items, itemItr);

		for (int i = 0; i < vecItems.size(); i++) 
		{
			Item item = vecItems[i];
			if (item.getLocation() == location) 
			{
				addToBagpack(item,itemItr);
			}
			else 
			{
				cout << "Item " << item.getName() << " is not available here" << endl;
			}
		}
	}

	void dropItem(ArrayIterator*& itemItr)
	{
		string choice;
		cout << "Bagpack is full. Do you want to drop some items?" << endl;
		getline(cin, choice);
		if (choice == "yes") 
		{
			string itemsToDrop;
			cout << "There are "<< bagpack << " in your bagpack" << endl;
			cout << "What do you want to drop?" << endl;
			getline(cin, itemsToDrop);
			vector<Item> vecItems = splitItems(itemsToDrop);
			for (Item item : vecItems)
			{
				item.setLocation(location);
				itemItr->addElement(item);
				bagpack->removeElement(bagpack->getIndex(item.getName()));
			}
		}
	}

	vector<Item> splitItems(string items, ArrayIterator*& itemItr) 
	{
		vector<Item> vecItems;
		char itemArr[50];
		strcpy_s(itemArr, items.c_str());
		char* remain = itemArr;
		char* token;

		while (token = strtok_s(remain, ",", &remain))
		{
			int index = -1;
			Item item;
			index = itemItr->getIndex(token);
			if (index >= 0)
			{
				item = (*itemItr)[index];
				vecItems.push_back(item);
			}
			else
			{
				cout << token << " is invalid" << endl;
			}
		}
		return vecItems;
	}

	vector<Item> splitItems(string items)
	{
		vector<Item> vecItems;
		char itemArr[50];
		strcpy_s(itemArr, items.c_str());
		char* remain = itemArr;
		char* token;

		while (token = strtok_s(remain, ",", &remain))
		{
			int index = -1;
			Item item;
			index = bagpack->getIndex(token);
			if (index >= 0)
			{
				item = (*bagpack)[index];
				vecItems.push_back(item);
			}
			else
			{
				cout << token << " is invalid" << endl;
			}
		}
		return vecItems;
	}

	void walk(vector<string> locations) 
	{
		string destination;
		bool valid = false;
		while (!valid)
		{
			cout << "Where do you want to go?" << endl;
			getline(cin, destination);
			if (destination == location)
			{
				cout << "You are already here" << endl;
				valid = true;
			}
			else if (find(begin(locations), end(locations), location) != end(locations)) {
				cout << "Walking to " << location << ".... Arrived" << endl;
				location = destination;
				valid = true;
			}
			else
			{
				cout << "Invalid location. Location available are class, library, canteen, rooftop and corridor" << endl;
			}
		}

	}

	void consumeFood();

};