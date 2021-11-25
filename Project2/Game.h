#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "Player.h"

class Game
{
	private:

	public:
		string mainMenu() 
		{
			string option;
			bool valid = false;
			cout << "----------------------" << endl;
			cout << "Welcome to Happy Farm" << endl;
			cout << "----------------------" << endl;
			cout << "1. Start" << endl;
			cout << "2. Quit" << endl;
			cout << "Enter your choice:";
			while (!valid) 
			{
				getline(cin, option);
				
				if (option == "1" || option == "2") 
				{
					valid = true;
				}
				else 
				{
					cout << "Invalid option...Try again" << endl;
				}
			}
			return option;
		}

		string actionMenu() 
		{
			string action;
			bool valid = false;
			cout << endl << "1. Buy Items" << endl;
			cout << "2. Sell Items" << endl;
			cout << "3. Plant" << endl;
			cout << "4. Harvest" << endl;
			cout << "5. Check Notifications" << endl;
			cout << "6. Talk to Mayor" << endl;
			cout << "7. Read Notes" << endl;
			cout << "8. Quit" << endl;
			cout << "Enter your choice:";
			while (!valid) 
			{
				getline(cin,action);
				cout << endl;
				if (action == "1" || action == "2" || action == "3" || action == "4" || action == "5" || action == "6" || action == "7" || action == "8")
				{
					valid = true;
				}	
				else 
				{
					cout << "Invalid option...Try again" << endl;
				}
			}
			return action;
		}

		string promptFarmName() 
		{
			string farmName;
			cout << endl << "Farm Name:";
			getline(cin, farmName);
			return farmName;
		}
		
		int promptLandSize() 
		{
			string sizeStr;
			int landSize;
			bool valid = false;


			while (!valid) 
			{
				cout << "Land Size:";
				getline(cin, sizeStr);

				try
				{
					landSize = stoi(sizeStr);
					if (landSize > 0) 
					{
						valid = true;
					}
					else 
					{
						cout << "Land size must be greater than zero..." << endl;
					}
					
				}
				catch (exception e) 
				{
					cout << "Invalid input...Only numbers" << endl;
				}
			}
			return landSize;
		}

		void printInventory(vector<Item> inventory) 
		{
			if (inventory.empty())
			{
				cout << "None" << endl;
			}
			else
			{
				for (unsigned int i = 0; i < inventory.size(); i++)
				{
					if (i < inventory.size() - 1)
					{
						cout << inventory[i].getName() << ",";
					}
					else
					{
						cout << inventory[i].getName() << endl;
					}
				}

			}
		}

		void displayDetails(Farm& farm,Player& player) 
		{
			cout << endl << farm.getName() << endl;
			cout << "Land Size:" << farm.getLandSize() << endl;
			cout << "Penny:" << player.getPenny() << endl;
			cout << "Inventory:";
			vector<Item> inventory = farm.getInventory();
			printInventory(inventory);
			cout << "Harvest Inventory:";
			vector<Item> harvestInventory = farm.getHarvestInventory();
			printInventory(harvestInventory);	
		}

		void start() 
		{
			bool run = true;
			string farmName = promptFarmName();
			int landSize = promptLandSize();
			Farm* farm = new Farm(landSize, farmName);
			Player* player = new Player(*farm);
			Visitor* visitor = nullptr;

			while (run) 
			{
				Sleep(250);
				system("clear");
				farm->checkForHarvest(player->getNotifications());
				displayDetails(*farm, *player);
				string action = actionMenu();
				Sleep(250);
				system("clear");
				displayDetails(*farm, *player);
				if (action == "1") 
				{
					visitor = new VisitorBuy();
					player->accept(*visitor);
					delete visitor;
					visitor = nullptr;
				}
				else if (action == "2") 
				{
					visitor = new VisitorSell();
					player->accept(*visitor);
					delete visitor;
					visitor = nullptr;
				}
				else if (action == "3") 
				{
					visitor = new VisitorPlant();
					player->accept(*visitor);
					delete visitor;
					visitor = nullptr;
				}
				else if (action == "4") 
				{
					visitor = new VisitorHarvest();
					player->accept(*visitor);
					delete visitor;
					visitor = nullptr;
				}
				else if (action == "5") 
				{
					visitor = new VisitorCheckNotifications();
					player->accept(*visitor);
					delete visitor;
					visitor = nullptr;
				}
				else if (action == "6") 
				{
					visitor = new VisitorTalk();
					player->accept(*visitor);
					delete visitor;
					visitor = nullptr;
				}
				else if (action == "7")
				{
					visitor = new VisitorReadNotes();
					player->accept(*visitor);
					delete visitor;
					visitor = nullptr;
				}
				else if (action == "8")
				{
					delete player;
					run = false;
				}
			}
			
		}
};