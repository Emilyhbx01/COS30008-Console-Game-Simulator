#include "GroupADT.h"
#include "Livestock.h"
#include "Item.h"

GroupADT::GroupADT()
{
	plantations = {};
	animalsReared = {};
}

vector<Livestock> GroupADT::getPlantations()
{
	return plantations;
}

vector<Livestock> GroupADT::getAnimalsReared()
{
	return animalsReared;
}

void GroupADT::setPlantations(vector<Livestock> plantationVector)
{
	plantations = plantationVector;
}

void GroupADT::setAnimalsReared(vector<Livestock> animalsVector)
{
	animalsReared = animalsVector;
}

void GroupADT::display()
{

	cout << endl << "------------------------------" << endl;
	cout << "Plantations Ready For Harvest" << endl;
	cout << "------------------------------" << endl;
	if (plantations.empty())
	{
		cout << "No plants ready for harvest..." << endl;
	}
	else
	{
		for (Livestock livestock : plantations)
		{
			cout << "Plant Name:" << livestock.getItem().getName() << endl;
			cout << "Quantity:" << livestock.getItem().getQuantity() << endl << endl;
		}

	}

	cout << endl << "--------------------------" << endl;
	cout << "Animals Ready For Harvest" << endl;
	cout << "--------------------------" << endl;

	if (animalsReared.empty())
	{
		cout << "No animals ready for harvest..." << endl;
	}
	else
	{
		for (Livestock livestock : animalsReared)
		{
			cout << "Animal Name:" << livestock.getItem().getName() << endl;
			cout << "Quantity:" << livestock.getItem().getQuantity() << endl << endl;
		}
	}


}

