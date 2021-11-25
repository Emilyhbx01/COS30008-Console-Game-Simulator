#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "Livestock.h"

class GroupADT 
{
	private:
		vector<Livestock> plantations;
		vector<Livestock> animalsReared;
	
	public:
		GroupADT();
		vector<Livestock> getPlantations();
		vector<Livestock> getAnimalsReared();
		void setPlantations(vector<Livestock> plantationVector);
		void setAnimalsReared(vector<Livestock> animalsVector);
		void display();

};