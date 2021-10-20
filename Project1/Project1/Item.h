#pragma once
#include <iostream>
using namespace std;


class Item 
{

	private:
		string name;
		string location;
		string useMessage;

	public:
		Item();
		Item(string itemName, string itemLocation, string message);
		string getName();
		string getMessage();
		void setLocation(string itemLocation);
		string getLocation();
};