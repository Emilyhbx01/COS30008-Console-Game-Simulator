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

Item::Item (string itemName, int cost, int sellPrice, int itemQuantity, string itemMessage, int time, string itemType)
{
	name = itemName;
	costPrice = cost;
	sellingPrice = sellPrice;
	quantity = itemQuantity;
	message = itemMessage;
	growthTime = time;
	type = itemType;
}

string Item::getName()
{
	return name;
}

int Item::getCostPrice()
{
	return costPrice;
}

int Item::getSellingPrice()
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

string Item::getType() 
{
	return type;
}


void Item::displayDetails(string type) 
{
	//cout << "Name:" << name << endl;
	//cout << "Cost Price:" << costPrice << endl;
	//cout << "Selling Price:" << sellingPrice << endl;
	//if (type == "harvest") 
	//{
	//	cout << "Quantity:" << quantity << endl;
	//}
	//cout << "Growth Time:" << growthTime << endl << endl;
	cout << "Name:" << name << ", Cost Price:" << costPrice << ", Selling Price:" << sellingPrice;
	if (type == "harvest")
	{
		cout << ", Quantity:" << quantity;
	}
	cout << ", Growth Time:" << growthTime << endl;
	
}

void Item::setQuantity(int itemQuantity) 
{
	quantity = itemQuantity;
}