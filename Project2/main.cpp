#include <iostream>
using namespace std;
#include "Game.h"


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


	//system("clear");
	//cout << "Test:" << x << endl;

	//if (stoi(x) > 10) {
	//	Sleep(10000);
	//}
	



	
	

	return 0;
}