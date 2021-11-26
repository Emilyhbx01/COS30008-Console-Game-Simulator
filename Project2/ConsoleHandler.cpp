#include "ConsoleHandler.h"
#include "Farm.h"
#include "Item.h"

ConsoleHandler::ConsoleHandler() {};

void ConsoleHandler::clearScreen()
{
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0,0 };

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
	{
		return;
	}

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
	{
		return;
	}
	else
	{
		cellCount = csbi.dwSize.X * csbi.dwSize.Y;
	}

	if (!FillConsoleOutputCharacter(hStdout, (TCHAR)' ', cellCount, homeCoords, &count))
	{
		return;
	}

	if (!FillConsoleOutputAttribute(hStdout, csbi.wAttributes, cellCount, homeCoords, &count))
	{
		return;
	}
	SetConsoleCursorPosition(hStdout, homeCoords);
}

void ConsoleHandler::setCursorPosition(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hStdout, coord);
}

COORD ConsoleHandler::getCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	COORD currentPos = { 0, 0 };
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
	{
		currentPos = cbsi.dwCursorPosition;
	}
	return currentPos;
}



void ConsoleHandler::printInventory(vector<Item> inventory)
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



void ConsoleHandler::updateConsole(COORD latestPos, Farm& farm, int penny)
{
	fillSpace({ 0,3 });
	setCursorPosition(0, 3);
	cout << "Penny:" << penny;

	fillSpace({ 0,2 });
	setCursorPosition(0, 2);
	cout << "Land Size:" << farm.getLandSize();
	setCursorPosition(latestPos.X, latestPos.Y);

	fillSpace({ 0,4 });
	setCursorPosition(0, 4);
	cout << "Inventory:";
	vector<Item> updatedInventory = farm.getInventory();
	printInventory(updatedInventory);

	fillSpace({ 0,5 });
	setCursorPosition(0, 5);
	cout << "Harvest Inventory:";
	vector<Item> updatedHarvestInventory = farm.getHarvestInventory();
	printInventory(updatedHarvestInventory);
	setCursorPosition(latestPos.X, latestPos.Y);

}


void ConsoleHandler::fillSpace(COORD coord)
{
	HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD noOfCells;
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(handleOutput, &csbi))
	{
		return;
	}
	else
	{
		noOfCells = csbi.dwSize.X;
	}
	FillConsoleOutputCharacter(handleOutput, ' ', noOfCells, coord, &count);
}
