#pragma once
#include <iostream>
using namespace std;
#include "ConsoleHandler.h"

class Player;
class Item;
class Farm;
class Visitor;


class Game
{
	private:
		ConsoleHandler consoleHandler;
		string actionMenu();
		string promptFarmName();
		int promptLandSize();
		void printInventory(vector<Item> inventory);
		void displayDetails(Farm& farm, Player& player);

	public:
		string mainMenu();
		void start();
};