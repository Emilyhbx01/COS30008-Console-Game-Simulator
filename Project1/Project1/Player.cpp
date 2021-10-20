#include "Player.h"

Player::~Player()
{
	delete bagpack;
	delete droppedItemList;
	delete note;
}

Player::Player()
{
	bagpack = new VectorIterator(0, 5, vector<Item>{});
	droppedItemList = new SinglyLinkedList(3);
	energy = 100;
	location = "class";
	note = new Note();
};



string Player::getLocation()
{
	return location;
}

void Player::setLocation(string playerLocation)
{
	location = playerLocation;
}

int Player::getEnergy()
{
	return energy;
}

void Player::setEnergy(int energyLvl)
{
	energy = energyLvl;
}

bool Player::addToBagpack(Item item, ArrayIterator*& itemItr)
{
	//if bagpack is full(5 items), will have to ask player to drop item
	if (bagpack->full())
	{
		dropItem(itemItr);
		return false;
	}
	else
	{
		//if player grab an item, the item should be removed from the item array and added to the player's bag pack
		bagpack->addElement(item);
		cout << "Added " << item.getName() << " to your bag" << endl;
		itemItr->removeElement(itemItr->getIndex(item.getName()));
		return true;

	}

}

Item Player::removeFromBagpack(string itemName)
{
	//get the item object from the bagpack using its index
	int index = bagpack->getIndex(itemName);
	Item item = (*bagpack)[index];
	bagpack->removeElement(index);
	return item;

}


void Player::grabItem(ArrayIterator*& itemItr)
{
	string items;
	cout << endl << "What item do you want to collect?" << endl;
	getline(cin, items);

	//split the words of player input
	vector<Item> vecItems = splitItems(items, itemItr);

	for (unsigned int i = 0; i < vecItems.size(); i++)
	{
		Item item = vecItems[i];
		if (item.getLocation() == location)
		{
			//if not added means bagpack is full so break out of loop
			bool added = addToBagpack(item, itemItr);
			if (!added)
			{
				break;
			}
		}
		else
		{
			cout << "Item " << item.getName() << " is not available here" << endl;
		}
	}
}

void Player::dropItem(ArrayIterator*& itemItr)
{
	string choice;
	cout << "Bagpack is full. Do you want to drop some items?" << endl;
	getline(cin, choice);
	if (choice == "yes")
	{
		string itemsToDrop;
		cout << "There are " << bagpack << " in your bagpack" << endl;
		cout << "What do you want to drop?" << endl;
		getline(cin, itemsToDrop);
		vector<Item> vecItems = splitItems(itemsToDrop);
		for (Item item : vecItems)
		{
			//reset the dropped item location to the player's current location
			item.setLocation(location);
			itemItr->addElement(item);
			bagpack->removeElement(bagpack->getIndex(item.getName()));

			//add the dropped item to the droppedItemList
			SingleNode* node = new SingleNode(item);
			droppedItemList->append(node);

		}
	}
}

void Player::seeDroppedItems()
{
	droppedItemList->showContent();
}

//process player input by splitting each word of the input by comma 
vector<Item> Player::splitItems(string items, ArrayIterator*& itemItr)
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


//process player input by splitting each word of the input by comma 
vector<Item> Player::splitItems(string items)
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

void Player::walk(vector<string> locations)
{
	string destination;
	bool valid = false;
	while (!valid)
	{
		cout << endl << "Where do you want to go?" << endl;
		getline(cin, destination);
		if (destination == location)
		{
			cout << "You are already here" << endl;
			valid = true;
		}
		//check if the location input by player exists
		else if (find(begin(locations), end(locations), destination) != end(locations)) {
			cout << "Walking to " << destination << ".... Arrived" << endl;
			location = destination;
			valid = true;
		}
		else
		{
			cout << "Invalid location. Location available are class, library, canteen, rooftop and corridor" << endl;
		}
	}

}


void Player::seeBook(Stack* books)
{
	cout << "Walking over to the books..." << endl;
	string action;
	

	//after player read a book, the book will be removed from the stack
	//check if the stack of book is empty 
	while (!(books->isEmpty()))
	{
		cout << endl << "1) Read the book" << endl;
		cout << "2) See the next book" << endl;
		cout << "3) Finish" << endl;
		cout << "Choose an option:" << endl;
		getline(cin, action);
		if (action == "1")
		{
			readBook(books);
		}
		else if (action == "2")
		{
			//if player chooses to skip and see the next book, the previous book will be removed from the stack
			books->pop();
		}
		else if (action == "3")
		{
			break;
		}
		else
		{
			cout << "Invalid option" << endl;
		}
	}

	if (books->isEmpty())
	{
		cout << "No more books..." << endl;
	}
}

void Player::readBook(Stack* books)
{
	string choice;
	bool run = true;
	Book* book = books->peek();
	DoublyLinkedList* pages = book->getContent();
	pages->showContent();

	while (run)
	{
		cout << endl << "1) Flip book to next page" << endl;
		cout << "2) Go to previous page" << endl;
		cout << "3) Finish" << endl;
		cout << "Choose an option:" << endl;
		getline(cin, choice);


		if (choice == "1")
		{
			pages->next();
			pages->showContent();
		}
		else if (choice == "2")
		{
			pages->previous();
			pages->showContent();
		}
		else if (choice == "3")
		{
			run = false;
		}
	}


}



void Player::takeNote()
{
	int penItemIndex = bagpack->getIndex("pen");
	int bookItemIndex = bagpack->getIndex("book");

	//check if the player has pen and book in the bagpack
	if (penItemIndex >= 0 && bookItemIndex >= 0)
	{
		string noteContent;
		cout << endl << "Enter your note:" << endl;
		getline(cin, noteContent);

		//display message of writing note...
		cout << (*bagpack)[penItemIndex].getMessage() << endl;
		cout << (*bagpack)[bookItemIndex].getMessage() << endl;
		note->append(noteContent);
	}
	else
	{
		cout << "A pen and book is required to take notes..." << endl;
	}

}

void Player::viewNote()
{
	if (note->noteContent.length() > 0)
	{
		note->view();
	}
	else
	{
		cout << "No notes available at the moment..." << endl;
	}
}

void Player::callHelp(bool& callHelp)
{
	string number;
	cout << "Enter number to dial:" << endl;
	getline(cin, number);
	cout << "Dialing..." << endl;

	//help can only be reached if the number is 110
	if (number == "110")
	{
		cout << "Call answered... Help is on the way..." << endl;
		callHelp = true;
	}
	else
	{
		cout << "The number you called is unavailable..." << endl;
	}
}


void Player::signalForHelp(bool& win)
{
	string items;
	cout << endl << "What item do you want to use?" << endl;
	cout << "There are " << bagpack << " in your bagpack." << endl;
	getline(cin, items);
	vector<Item> itemsVec = splitItems(items);

	//player can only use warning light to signal sucessfully
	for (Item item : itemsVec)
	{
		if (item.getName() == "warning light" || item.getName() == "torchlight" || item.getName() == "fire extinguisher")
		{
			int index = bagpack->getIndex(item.getName());
			cout << (*bagpack)[index].getMessage() << endl;
			if (item.getName() == "warning light")
			{
				cout << "The helicopter is coming!!" << endl;
				win = true;
			}
		}
		else
		{
			cout << item.getName() << " cannot be used for signalling..." << endl;
		}


	}



}
void Player::consumeFood()
{
	string food;
	cout << "What food do you want to consume?" << endl;
	cout << "There are " << bagpack << " in your bag pack" << endl;
	getline(cin, food);
	vector<Item> foodVec = splitItems(food);

	for (Item item : foodVec)
	{
		string name = item.getName();
		if (name != "banana" && name != "bun" && name != "water")
		{
			cout << name << " is not consumable" << endl;
		}
		else
		{
			cout << item.getMessage() << endl;
			energy += 80;
			bagpack->removeElement(bagpack->getIndex(item.getName()));
		}
	}



}