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
		Item() {};
		Item(string itemName, string itemLocation,string message)
		{
			name = itemName;
			location = itemLocation;
			useMessage = message;
		}

		string getName() 
		{
			return name;
		}

		string getMessage() 
		{
			return useMessage;
		}

		void setLocation(string itemLocation) 
		{
			location = itemLocation;
		}

		string getLocation() 
		{
			return location;
		}
		
};