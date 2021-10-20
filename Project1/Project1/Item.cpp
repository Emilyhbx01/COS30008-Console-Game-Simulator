#include "Item.h"


Item::Item() {};
Item::Item(string itemName, string itemLocation, string message)
{
	name = itemName;
	location = itemLocation;
	useMessage = message;
}

string Item::getName()
{
	return name;
}

string Item::getMessage()
{
	return useMessage;
}

void Item::setLocation(string itemLocation)
{
	location = itemLocation;
}

string Item::getLocation()
{
	return location;
}

