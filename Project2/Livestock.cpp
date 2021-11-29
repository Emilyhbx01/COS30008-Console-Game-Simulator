#include "Livestock.h"


Livestock::Livestock() 
{
	item = Item();
	timePlanted = NULL;
	timeToHarvest = NULL;
}

Livestock::Livestock(Item aItem)
{
	item = aItem;
	//get time in seconds
	time_t timeNow = time(0);
	timePlanted = timeNow;
	timeToHarvest = item.getGrowthTime() + timeNow;
}

Item Livestock::getItem()
{
	return item;
}

bool Livestock::canHarvest()
{
	time_t timeNow = time(0);
	if (timeNow >= timeToHarvest)
	{
		return true;
	}
	return false;
}

time_t Livestock::getTimePlanted()
{
	return timePlanted;
}

time_t Livestock::getTimeToHarvest() 
{
	return timeToHarvest;
}