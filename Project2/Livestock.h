#pragma once
#include <iostream>
using namespace std;
#include <ctime>
#include "Item.h"

class Item;

class Livestock 
{
	private:
		Item item;
		time_t timePlanted;
		time_t timeToHarvest;

	public:
		Livestock();
		Livestock(Item aItem);
		Item getItem();
		time_t getTimePlanted();
		time_t getTimeToHarvest();
		bool canHarvest();
};