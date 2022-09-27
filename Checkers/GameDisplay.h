// GameDisplay.h

#pragma once

#ifndef GAMEDISPLAY_H
#define GAMEDISPLAY_H

#include "Checker.h"
#include "Game.h"

class GameDisplay
{
public:
	// Constructors
	GameDisplay();
	GameDisplay(std::string);

	// Destructor
	~GameDisplay();


private:
	// Logic Data Members
	int gameTick;
	float relativeX;
	float relativeY;
	Game* game;
	Checker* checkerInHand;
	Checker** fieldedCheckers;

	// Display Data Members
	sf::RenderWindow window;
	sf::Texture backgroundTexture;
	sf::Sprite background;
	sf::Event event;

	// Driver
	void eventListener();

	// Manipulator
	void drawAssets();
	void onLeftClick(int, int);
	void onLeftRelease(int, int);
	void onMouseMove(int, int);
	void updateFieldedCheckers();

	// Utility
	int pixToPos(float);
	int pixToPos(int);
	float posToPix(int);

};

#endif