#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "Item.h"

class Stack;
class Queue;
class GroupADT;

class Farm 
{
	private:
		int landSize;
		string name;
		Stack* notes;
		Item market[6] = { Item("Wheat", 1, 2, NULL, "Planting wheat...", 180, "plant"),
		Item("Corn", 1, 3, NULL, "Planting corn...", 180, "plant"),
		Item("Carrot", 2, 4, NULL, "Planting carrot...", 180, "plant"),
		Item("Chicken", 10, 20, NULL, "Rearing chicken...", 300, "animal"),
		Item("Pig", 20, 40, NULL, "Rearing pig...", 300, "animal"),
		Item("Sheep", 30, 50, NULL, "Rearing sheep...", 300, "animal")};

		Queue* plantations;
		Queue* animalsReared;
		vector<Item> inventory;
		vector<Item> harvestInventory;

	public:

		~Farm();
		Farm(int sizeOfLand, string farmName);
		int getLandSize();
		string getName();
		Queue* getPlantations();
		Queue* getAnimalsReared();
		vector<Item> getInventory();
		vector<Item> getHarvestInventory();
		Item* getMarket();
		Stack* getNotes();
		void setLandSize(int size);
		void setInventory(vector<Item> inventoryVec);
		void setHarvestInventory(vector<Item> harvestInventoryVec);
		void checkForHarvest(GroupADT& notifications);
};
