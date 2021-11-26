#pragma once
#include <iostream>
using namespace std;
#include <Windows.h>
#include <vector>

class Item;
class Farm;

class ConsoleHandler 
{
	public:
		ConsoleHandler();
		void clearScreen();
		void setCursorPosition(int x, int y);
		COORD getCursorPosition();
		void printInventory(vector<Item> inventory);
		void updateConsole(COORD latestPos, Farm& farm, int penny);
		void fillSpace(COORD coord);
};