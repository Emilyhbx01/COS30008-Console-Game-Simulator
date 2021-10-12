#include<iostream>
using namespace std;
#include "Game.h"
#include <SFML/Audio.hpp>
using namespace sf;




int main() 
{
	Music music;
	music.openFromFile("Audio/adventure.wav");
	music.setVolume(50);
	music.play();
	music.setLoop(true);

	Game game;
	string choice = game.menu();

	if (choice == "1") 
	{
		game.start();

	}
	else 
	{
		return 2;
	}

	

	return 0;
}

