#include "Game.h"
#include <string>
#include "Player.h"
#include "Item.h"
#include "Farm.h"
#include "Visitor.h"

string Game::actionMenu()
{
	string action;
	bool valid = false;
	cout << endl << "1. Buy Items" << endl;
	cout << "2. Sell Items" << endl;
	cout << "3. Plant" << endl;
	cout << "4. Harvest" << endl;
	cout << "5. Check Notifications" << endl;
	cout << "6. View Plantations & Animals Reared" << endl;
	cout << "7. Talk to Mayor" << endl;
	cout << "8. Read Notes" << endl;
	cout << "9. Quit" << endl;
	cout << "Enter your choice:";
	while (!valid)
	{
		getline(cin, action);
		cout << endl;
		if (action == "1" || action == "2" || action == "3" || action == "4" || action == "5" || action == "6" || action == "7" || action == "8" || action == "9")
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

string Game::promptFarmName()
{
	string farmName;
	cout << endl << "Farm Name:";
	getline(cin, farmName);
	return farmName;
}

int Game::promptLandSize()
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

void Game::printInventory(vector<Item> inventory)
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
				cout << inventory[i].getName() << " x" << inventory[i].getQuantity() << ",";
			}
			else
			{
				cout << inventory[i].getName() << " x" << inventory[i].getQuantity() << endl;
			}
		}

	}
}


void Game::displayDetails(Farm& farm, Player& player)
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


string Game::mainMenu()
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


void Game::start()
{
	bool run = true;
	string farmName = promptFarmName();
	int landSize = promptLandSize();
	Farm* farm = new Farm(landSize, farmName);
	Player* player = new Player(*farm);
	Visitor* visitor = nullptr;

	while (run)
	{
		consoleHandler.clearScreen();
		farm->checkForHarvest(player->getNotifications());
		displayDetails(*farm, *player);
		string action = actionMenu();
		consoleHandler.clearScreen();
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
			visitor = new VisitorViewPlantations();
			player->accept(*visitor);
			delete visitor;
			visitor = nullptr;
		}
		else if (action == "7")
		{
			visitor = new VisitorTalk();
			player->accept(*visitor);
			delete visitor;
			visitor = nullptr;
		}
		else if (action == "8")
		{
			visitor = new VisitorReadNotes();
			player->accept(*visitor);
			delete visitor;
			visitor = nullptr;
		}
		else if (action == "9")
		{
			delete player;
			run = false;
		}
	}

}
