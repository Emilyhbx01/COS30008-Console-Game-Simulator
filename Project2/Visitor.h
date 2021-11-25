#pragma once
#include <iostream>
using namespace std;

class Player;	//forward declaration

class Visitor 
{
	public:
		virtual void visit(Player& player);

};

class VisitorBuy : public Visitor
{
	public:
		void visit(Player& player);
};

class VisitorPlant : public Visitor 
{
	public:
		void visit(Player& player);
};

class VisitorHarvest : public Visitor 
{
	public:
		void visit(Player& player);
};

class VisitorReadNotes : public Visitor
{
	public:
		void visit(Player& player);
};

class VisitorTalk : public Visitor
{
	public:
		void visit(Player& player);
};

class VisitorCheckNotifications : public Visitor
{
public:
	void visit(Player& player);
};

class VisitorSell : public Visitor 
{
	public:
	void visit(Player& player);
};