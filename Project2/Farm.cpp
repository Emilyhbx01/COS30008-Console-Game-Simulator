#include "Farm.h"
#include "Stack.h"
#include "Queue.h"
#include "GroupADT.h"
#include "Note.h"


Farm::~Farm()
{
	delete notes;
	delete plantations;
	delete animalsReared;
}

Farm::Farm(int sizeOfLand, string farmName)
{
	landSize = sizeOfLand;
	name = farmName;
	notes = new Stack
	(
		vector<Note>
	{
		Note("Best Seed To Plant", "There are different kinds of seeds available in the market.\nHowever, you can choose the best seed which produces greater income within the same amount of time.\nCorn and carrot would be the most profitable seeds.\n"),
			Note("Calculating Profit", "Choose the right animal to rear in order to gain a better earning.\nProfit can be calculated using the formula:\nProfit = Cost Price - Selling Price\n")
	}
	);

	plantations = new Queue();
	animalsReared = new Queue();
	inventory = {};
	harvestInventory = {};
}

int Farm::getLandSize()
{
	return landSize;
}

string Farm::getName()
{
	return name;
}

Queue* Farm::getPlantations()
{
	return plantations;
}

Queue* Farm::getAnimalsReared()
{
	return animalsReared;
}

vector<Item> Farm::getInventory()
{
	return inventory;
}

vector<Item> Farm::getHarvestInventory()
{
	return harvestInventory;
}

Item* Farm::getMarket()
{
	return market;
}

Stack* Farm::getNotes()
{
	return notes;
}
void Farm::setLandSize(int size)
{
	landSize = size;
}

void Farm::setInventory(vector<Item> inventoryVec)
{
	inventory = inventoryVec;
}

void Farm::setHarvestInventory(vector<Item> harvestInventoryVec)
{
	harvestInventory = harvestInventoryVec;
}

void Farm::checkForHarvest(GroupADT& notifications)
{
	plantations->readyForHarvest(notifications);
	animalsReared->readyForHarvest(notifications);
}
