#pragma once
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
		string playerLocation;
		bool win;
		bool callHelp;
		Player player;


	public:
		~Game();
		Game();
		string menu();
		void initializeArrays();
		void start();
		string promptAction();
		void initilizeBookStack();
		
};