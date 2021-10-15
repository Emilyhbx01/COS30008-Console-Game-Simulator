#include "Game.h"

Game::~Game()
{
	delete itemItr;
	delete books;
}

Game::Game()
{

	initializeArrays();
	win = false;
	callHelp = false;
	books = new Stack(3);
	playerLocation = player.getLocation();

}



string Game::menu()
{

	string choice;
	bool valid = false;
	cout << "_________________________" << endl << endl;
	cout << "Welcome to Escape" << endl;
	cout << "_________________________" << endl << endl;
	cout << "In this game, there will be five locations which are class, library, corridor, canteen and rooftop.\nIn order to win this game, you must stay find information in the library and call for help.\nAfter you successfully call for help, you must signal for help at the rooftop." << endl;
	cout << "You have a limited amount of energy which will decrease gradually in the game.\nConsume food to ensure that you can survive." << endl << endl;
	cout << "1) Start Game" << endl;
	cout << "2) Quit" << endl;

	while (!valid)
	{
		cout << "Enter your choice:" << endl;
		getline(cin, choice);
		if (choice == "1" || choice == "2")
		{
			valid = true;
		}
		else
		{
			cout << "Invalid input" << endl;
		}
	}
	return choice;
}

//initialize an array iterator for the item array
void Game::initializeArrays()
{
	Item* items = new Item[12]{ Item("book","class","Taking note..."), Item("pen","class","Writing..."), Item("marker","class","Writing..."),Item("torchlight","corridor","Turning on...The light is not bright enough!"), Item("warning light","corridor", "Turning on...It's coming!!"), Item("fire extinguisher","corridor","Spraying...It's not eye-catching enough!"),Item("banana","canteen","Eating banana..."), Item("bun","canteen","Eating bun..."),Item("water","canteen","Drinking...") };
	locations = { "class","canteen","corridor","library","rooftop" };
	itemItr = new ArrayIterator(items, 0, 9);

}

void Game::start()
{
	cout << endl << "I woke up from a nap as I remember I came to school this morning but what happened.\nThere's no one around me. Where are all my classmates?The school has never been this quiet.\nI could see zombies walking around outside the school building." << endl;
	
	//player lose if energy level drops below 10
	while (!win && player.getEnergy() >= 10)
	{
		player.setEnergy(player.getEnergy() - 10);
		playerLocation = player.getLocation();

		if (player.getEnergy() <= 30)
		{
			cout << "Warning! Your energy level is low. Get some food!" << endl;
		}

		string choice = promptAction();



		if (choice == "1")
		{
			player.walk(locations);
		}
		else if (choice == "2")
		{
			player.consumeFood();
		}
		else if (choice == "3")
		{
			player.seeDroppedItems();
		}
		else if (choice == "4" && playerLocation != "library" && playerLocation != "rooftop")
		{
			player.grabItem(itemItr);
		}
		else if (playerLocation == "library")
		{
			if (books->isEmpty())
			{
				initilizeBookStack();
			}

			if (choice == "4")
			{
				player.seeBook(books);
			}
			else if (choice == "5")
			{
				player.takeNote();
			}
			else if (choice == "6")
			{
				player.viewNote();
			}
			else if (choice == "7")
			{
				player.callHelp(callHelp);
			}
			else
			{
				cout << "Invalid option" << endl;
			}
		}
		else if (playerLocation == "rooftop")
		{
			if (callHelp == true && choice == "4")
			{
				player.signalForHelp(win);

			}
			else
			{
				cout << "Invalid option" << endl;
			}
		}
		else
		{
			cout << "Invalid option" << endl;
		}
	}

	if (!win && player.getEnergy() < 10)
	{
		cout << "Out of energy. You lost." << endl;
	}

}

//different locations will have different options of player actions
string Game::promptAction()
{
	string choice;

	if (playerLocation == "library")
	{
		cout << endl << "There's a stack of books which seems informative and also a phone which seems to be working well." << endl;
	}

	if (playerLocation == "rooftop")
	{
		if (callHelp)
		{
			cout << endl << "There's a helicopter far away!!" << endl;
		}
	}

	if (playerLocation != "library")
	{
		itemItr->displayItems(playerLocation);
	}

	cout << endl << "What do you want to do?" << endl;
	cout << "1) Go other location" << endl;
	cout << "2) Consume food" << endl;
	cout << "3) View dropped items" << endl;

	if (playerLocation != "library" && playerLocation != "rooftop")
	{
		cout << "4) Collect some items" << endl;
	}
	else if (playerLocation == "library")
	{
		cout << "4) Look at books" << endl;
		cout << "5) Take note" << endl;
		cout << "6) View note" << endl;
		cout << "7) Use phone" << endl;
	}
	else if (playerLocation == "rooftop")
	{
		if (callHelp)
		{
			cout << "4) Signal for help" << endl;
		}
	}



	getline(cin, choice);
	return choice;
}

//create a stack of book in the library
void Game::initilizeBookStack()
{
	//each book will have 2 pages
	DoubleNode* page1 = new DoubleNode("\nGeneral Hospital: 082-555555\nTing Vet: 082-555444\nHilton: 082-777888");
	DoubleNode* page2 = new DoubleNode("\nNational Police Academy: 082-333444\nArmy Force: 082-111222\nEmergency Contact(24 hours): 110");
	DoublyLinkedList* pages = new DoublyLinkedList(page1, page1);
	pages->append(page2);
	books->push(new Book("Yellow Pages", "This book contains a list of phone numbers for services", pages));

	page1 = new DoubleNode("\nThe worst was coming. Everyone who got bitten changed.\nWe were the only ones standing trying to find a way out.\nAlmost all levels of the building is filled with zombies.\nThe only way to survive now is to get to the rooftop and signal for help.\n");
	page2 = new DoubleNode("\nAs long as I keep quiet, the zombies won't be able to sense my presence.\nI crept to the phone and dialed 110 to get help.\nFinally, there was a voice 'Hello, how can I help you?'\n");
	pages = new DoublyLinkedList(page1, page1);
	pages->append(page2);
	books->push(new Book("Zombie Apocalypse", "This book is about a zombie attack that occured in an hospital", pages));

	page1 = new DoubleNode("\nIn times of emergency, stay calm and call for help if possible.\nGet to the highest place possible to signal for help.\n");
	page2 = new DoubleNode("\nWhen you are in danger, call the Emergency Contact at 110\nand tell them your situation so they can plan how to rescue you.\n");
	pages = new DoublyLinkedList(page1, page1);
	pages->append(page2);
	books->push(new Book("Emergency Act", "This book is about handling different kinds of emergency situations", pages));

}