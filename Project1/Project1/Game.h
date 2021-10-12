#pragma once
#include <iostream>
using namespace std;
#include "Player.h"
#include "Item.h"
#include "IteratorBase.h"
#include "ArrayIterator.h"
#include <string>
#include <ctime>

class Game 
{
	private:
		ArrayIterator* itemItr;
		vector<string> locations;
		int timeLimit;
		int timeUp;
		bool win;
		Player player;


	public:
		~Game() 
		{
			delete itemItr;
		}

		Game()
		{
			initializeArrays();
			timeLimit = 300;
			win = false;
			timeUp = false;
			
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
			Item* items = new Item[12]{ Item("book","class","Taking note..."), Item("pen","class","Taking note..."), Item("marker","class","Writing..."),Item("torchlight","corridor","Turning on...The light is not bright enough!"), Item("warning light","corridor", "Turning on...It's coming!!"), Item("fire extinguisher","corridor","Spraying...It's not eye-catching enough!"),Item("banana","canteen","Eating..."), Item("bun","canteen","Eating..."),Item("water","canteen","Drinking..."),Item("phone","library","Dialing..."), Item("phone book","library","Reading"),Item("computer","library","Browsing...")};
			locations = {"class","canteen","corridor","library","rooftop"};
			itemItr = new ArrayIterator(items, 0, 12);

		}

		void start()
		{
			time_t timeStart, timeFinish;
			time(&timeStart);

			cout << endl << "I woke up from a nap as I remember I came to school this morning but what happened. There's no one around me. Where are all my classmates? The school has never been this quiet. I could see zombies walking around outside the school building." << endl;
			while (!win && !timeUp) 
			{
				time(&timeFinish);
				if (difftime(timeFinish, timeStart) >= timeLimit) 
				{
					timeUp = true;
					break;
				}
				string choice = promptAction();

				if (choice == "1")
				{
					player.walk(locations);
				}
				else if (choice == "2")
				{
					player.grabItem(itemItr);
				}

			}
			
		
		}

		string promptAction()
		{
			string choice;
			string playerLocation = player.getLocation();
			itemItr->displayItems(playerLocation);
			cout << "What do you want to do?" << endl;
			cout << "1) Go other location" << endl;
			cout << "2) Collect some items" << endl;

			getline(cin,choice);
			return choice;
		}


		
		string promptLocation() 
		{
			string location;
			bool valid = false;
			while (!valid) 
			{
				cout << "Where do you want to go?" << endl;
				getline(cin,location);
				if (location == player.getLocation())
				{
					cout << "You are already here" << endl;
					valid = true;
				}
				else if (find(begin(locations), end(locations), location) != end(locations)) {
					cout << "Walking to " << location << ".... Arrived" << endl;
					player.setLocation(location);
					valid = true;
				}
				else
				{
					cout << "Invalid location. Location available are class, library, canteen, rooftop and corridor" << endl;
				}
			}
			return location;
			
		}
};