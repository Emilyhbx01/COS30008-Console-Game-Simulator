#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "ConsoleHandler.h"

class Farm;
class GroupADT;
class Visitor;
template <class T> class BTree;
class Livestock;



class Player 
{
	private:
		ConsoleHandler consoleHandler;
		int penny;
		Farm* farm;
		GroupADT* notifications;
		BTree<string>* convoTree;
		void initializeTree();
		

	public:
		~Player();
		Player(Farm& aFarm);
		void plant();
		void buy();
		void readNotes();
		void harvest();
		vector<Livestock> updateHarvestInventory(vector<Livestock> livestock, string name);
		void talk();
		void sell();
		void checkNotifications();
		void accept(Visitor& visitor);
		int getPenny();
		GroupADT& getNotifications();
		void viewPlantations();
};