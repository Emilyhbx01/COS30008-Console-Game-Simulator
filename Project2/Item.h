#pragma once
#include <iostream>
using namespace std;

class Item 
{
	private:
		string name;
		string message;
		string type;
		int costPrice;
		int sellingPrice;
		int quantity;
		int growthTime;

	public:
		Item();
		Item(string itemName, int cost, int sellPrice, int itemQuantity, string itemMessage, int time,string itemType);
		string getName();
		int getCostPrice();
		int getSellingPrice();
		int getQuantity();
		string getMessage();
		string getType();
		int getGrowthTime();
		void displayDetails(string type);
		void setQuantity(int itemQuantity);
		


};