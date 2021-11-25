#include "Visitor.h"
#include "Player.h"


void Visitor::visit(Player& player) 
{
	
}

void VisitorBuy::visit(Player& player) 
{
	player.buy();
}


void VisitorPlant::visit(Player& player) 
{
	player.plant();
}


void VisitorHarvest::visit(Player& player) 
{
	player.harvest();
}


void VisitorReadNotes::visit(Player& player) 
{
	player.readNotes();
}



void VisitorTalk::visit(Player& player) 
{
	player.talk();
}

void VisitorCheckNotifications::visit(Player& player) 
{
	player.checkNotifications();
}

void VisitorSell::visit(Player& player) 
{
	player.sell();
}
