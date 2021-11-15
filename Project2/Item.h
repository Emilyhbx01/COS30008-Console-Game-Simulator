#pragma once
#include <iostream>
using namespace std;

class Item 
{
	private:
		string name;
		string message;
		double costPrice;
		double sellingPrice;
		int quantity;
		int growthTime;

	public:
		Item();
		Item(string itemName, double cost, double sellPrice, int itemQuantity, string itemMessage, int time);
		string getName();
		double getCostPrice();
		double getSellingPrice();
		int getQuantity();
		string getMessage();
		int getGrowthTime();


};