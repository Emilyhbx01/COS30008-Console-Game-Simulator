#include "Item.h"


Item::Item() 
{
	name = "";
	costPrice = NULL;
	sellingPrice = NULL;
	quantity = NULL;
	message = "";
	growthTime = NULL;

}

Item::Item (string itemName, double cost, double sellPrice, int itemQuantity, string itemMessage, int time)
{
	name = itemName;
	costPrice = cost;
	sellingPrice = sellPrice;
	quantity = itemQuantity;
	message = itemMessage;
	growthTime = time;
}

string Item::getName()
{
	return name;
}

double Item::getCostPrice()
{
	return costPrice;
}

double Item::getSellingPrice()
{
	return sellingPrice;
}

int Item::getQuantity()
{
	return quantity;
}

string Item::getMessage() 
{
	return message;
}

int Item::getGrowthTime() 
{
	return growthTime;
}