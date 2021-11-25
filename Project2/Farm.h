#pragma once
#include <iostream>
using namespace std;
#include "Stack.h"
#include "Item.h"
#include "Queue.h"

class Farm 
{
	private:
		int landSize;
		string name;
		Stack* notes;
		Item market[6];
		Queue* plantations;
		Queue* animalsReared;
		vector<Item> inventory;
		vector<Item> harvestInventory;

	public:

		~Farm() 
		{
			delete notes;
			delete plantations;
			delete animalsReared;
		}
		
		Farm(int sizeOfLand, string farmName) 
		{
			landSize = sizeOfLand;
			name = farmName;
			notes = new Stack
			(
				vector<Note>
				{
				Note("Best Seed To Plant","There are different kinds of seeds available in the market.\nHowever, you can choose the best seed which produces greater income within the same amount of time.\nCorn and carrot would be the most profitable seeds.\n"),
				Note("Calculating Profit", "Choose the right animal to rear in order to gain a better earning.\nProfit can be calculated using the formula:\nProfit = Cost Price - Selling Price\n")
				}
			);

			market[0] = Item("Wheat", 1, 2, NULL, "Planting wheat...", 180,"plant");
			market[1] = Item("Corn", 1, 3, NULL, "Planting corn...", 180,"plant");
			market[2] = Item("Carrot", 2, 4, NULL, "Planting carrot...", 180,"plant");
			market[3] = Item("Chicken", 10, 20, NULL, "Rearing chicken...", 300,"animal");
			market[4] = Item("Pig", 20, 40, NULL, "Rearing pig...", 5,"animal");
			market[5] = Item("Sheep", 30, 50, NULL, "Rearing sheep...", 300,"animal");
			
			plantations = new Queue();
			animalsReared = new Queue();
			inventory = {};
			harvestInventory = {};
		}

		int getLandSize() 
		{
			return landSize;
		}

		string getName() 
		{
			return name;
		}

		Queue* getPlantations() 
		{
			return plantations;
		}

		Queue* getAnimalsReared() 
		{
			return animalsReared;
		}

		vector<Item> getInventory() 
		{
			return inventory;
		}

		vector<Item> getHarvestInventory() 
		{
			return harvestInventory;
		}

		Item* getMarket()
		{
			return market;
		}

		Stack* getNotes()
		{
			return notes;
		}
		void setLandSize(int size) 
		{
			landSize = size;
		}

		void setInventory(vector<Item> inventoryVec) 
		{
			inventory = inventoryVec;
		}

		void setHarvestInventory(vector<Item> harvestInventoryVec) 
		{
			harvestInventory = harvestInventoryVec;
		}

		void checkForHarvest(GroupADT& notifications) 
		{
			plantations->readyForHarvest(notifications);
			animalsReared->readyForHarvest(notifications);
		}
};
