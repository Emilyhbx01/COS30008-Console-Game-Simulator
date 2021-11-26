#include <iostream>
using namespace std;
#include "Game.h"

#include "Queue.h"
#include "Livestock.h"
#include "SingleNode.h"
int main() 
{
	Game* game = new Game();
	string option = game->mainMenu();
	if (option == "1") 
	{
		game->start();
	}
	else 
	{
		delete game;
		return 1;
	}
	delete game;

	return 0;
}