#pragma once
#include <iostream>
using namespace std;
#include "Player.h"
#include "Item.h"
#include "IteratorBase.h"
#include "ArrayIterator.h"
#include <string>
#include <ctime>
#include "Stack.h"

class Game 
{
	private:
		ArrayIterator* itemItr;
		Stack* books;
		vector<string> locations;
		bool win;
		bool callHelp;
		Player player;


	public:
		~Game() 
		{
			delete itemItr;
			delete books;
		}

		Game()
		{

			initializeArrays();
			win = false;
			callHelp = false;
			
		}

		

		string menu()
		{
			
			string choice;
			bool valid = false;
			cout << "Welcome to Escape. To win this game, you will have to find a way to call and signal for help within 5 minutes." << endl;
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

		void initializeArrays()
		{
			Item* items = new Item[12]{ Item("book","class","Taking note..."), Item("pen","class","Writing..."), Item("marker","class","Writing..."),Item("torchlight","corridor","Turning on...The light is not bright enough!"), Item("warning light","corridor", "Turning on...It's coming!!"), Item("fire extinguisher","corridor","Spraying...It's not eye-catching enough!"),Item("banana","canteen","Eating..."), Item("bun","canteen","Eating..."),Item("water","canteen","Drinking...")};
			locations = {"class","canteen","corridor","library","rooftop"};
			itemItr = new ArrayIterator(items, 0, 9);

		}

		void start()
		{
			string playerLocation;
			cout << endl << "I woke up from a nap as I remember I came to school this morning but what happened. There's no one around me. Where are all my classmates? The school has never been this quiet. I could see zombies walking around outside the school building." << endl;
			while (!win) 
			{
				playerLocation = player.getLocation();
				if (playerLocation != "library" && playerLocation != "rooftop") 
				{
					string choice = promptAction(playerLocation);

					if (choice == "1")
					{
						player.walk(locations);
					}
					else if (choice == "2")
					{
						player.grabItem(itemItr);
					}
					else if (choice == "3")
					{
						player.seeDroppedItems();
					}
				}
				else if (playerLocation == "library") 
				{
					promptLibraryAction();
				}
				else if (playerLocation == "rooftop") 
				{
					promptRooftopAction();
				}
				

			}
			
		
		}

		string promptAction(string& playerLocation)
		{
			string choice;
			
			itemItr->displayItems(playerLocation);
			cout << "What do you want to do?" << endl;
			cout << "1) Go other location" << endl;
			cout << "2) Collect some items" << endl;
			cout << "3) View dropped items" << endl;
			
			getline(cin,choice);
			return choice;
		}

		void promptLibraryAction() 
		{
			string choice;
			initilizeBookStack();
			cout << endl << "There's a stack of books which seems informative and also a phone which seems to be working well." << endl;
			cout << "What do you want to do?" << endl;
			cout << "1) Go other location" << endl;
			cout << "2) View dropped items" << endl;
			cout << "3) Look at books" << endl;
			cout << "4) Take note" << endl;
			cout << "5) View note" << endl;
			cout << "6) Use phone" << endl;
			getline(cin, choice);

			if (choice == "1") 
			{
				player.walk(locations);
			}
			else if (choice == "2") 
			{
				player.seeDroppedItems();
			}
			else if (choice == "3") 
			{
				player.seeBook(books);
			}
			else if (choice == "4") 
			{
				player.takeNote();
			}
			else if (choice == "5") 
			{
				player.viewNote();
			}
			else if (choice == "6") 
			{
				player.callHelp(callHelp);
			}
			else
			{
				cout << "Invalid option" << endl;
			}
		}


		void promptRooftopAction() 
		{
			string choice;
			if (callHelp) 
			{
				cout << endl << "There's a helicopter far away!!" << endl;
				cout << "What do you want to do?" << endl;
				cout << "1) Go other location" << endl;
				cout << "2) View dropped items" << endl;
				cout << "3) Signal for help" << endl;
				getline(cin, choice);

				if (choice == "1")
				{
					player.walk(locations);
				}
				else if (choice == "2")
				{
					player.seeDroppedItems();
				}
				else if (choice == "3")
				{
					player.signalForHelp();
				}
				else
				{
					cout << "Invalid option" << endl;
				}
			}
			else 
			{
				cout << "What do you want to do?" << endl;
				cout << "1) Go other location" << endl;
				cout << "2) View dropped items" << endl;
				getline(cin, choice);

				if (choice == "1")
				{
					player.walk(locations);
				}
				else if (choice == "2")
				{
					player.seeDroppedItems();
				}
			}
			


			
			
		}

		void initilizeBookStack() 
		{
			books = new Stack(3);
			DoubleNode* page1 = new DoubleNode("\nGeneral Hospital: 082-555555\nTing Vet: 082-555444\nHilton: 082-777888");
			DoubleNode* page2 = new DoubleNode("\nNational Police Academy: 082-333444\nArmy Force: 082-111222\nEmergency Contact(24 hours): 110");
			DoublyLinkedList* pages = new DoublyLinkedList(page1,page1);
			pages->append(page2);
			books->push(new Book("Yellow Pages", "This book contains a list of phone numbers for services", pages));
			
			page1 = new DoubleNode("\nThe worst was coming. Everyone who got bitten changed.\nWe were the only ones standing trying to find a way out.\nAlmost all levels of the building is filled with zombies.\nThe only way to survive now is to get to the rooftop and signal for help.\n");
			page2 = new DoubleNode("\nAs long as I keep quiet, the zombies won't be able to sense my presence.\nI crept to the phone and dialed 110 to get help.\nFinally, there was a voice 'Hello, how can I help you?'\n");
			pages = new DoublyLinkedList(page1, page1);
			pages->append(page2);
			books->push(new Book("Zombie Apocalypse", "This book is about a zombie attack that occured in an hospital",pages));

			page1 = new DoubleNode("\nIn times of emergency, stay calm and call for help if possible.\nGet to the highest place possible to signal for help.\n");
			page2 = new DoubleNode("\nWhen you are in danger, call the Emergency Contact at 110\nand tell them your situation so they can plan how to rescue you.\n");
			pages = new DoublyLinkedList(page1, page1);
			pages->append(page2);
			books->push(new Book("Emergency Act", "This book is about handling different kinds of emergency situations", pages));
			
		}
};