// GameDisplay.cpp

#include "stdafx.h"
#include "GameDisplay.h"

using namespace std;

// Constructors

GameDisplay::GameDisplay() : checkerInHand(NULL), fieldedCheckers(NULL)
{
	gameTick = 0;
	window.create(sf::VideoMode(800, 800), "Checkers!");
	window.setVerticalSyncEnabled(true);
	backgroundTexture.loadFromFile("draughts_board.png");
	background = sf::Sprite(backgroundTexture);
	game = new Game();
	updateFieldedCheckers();
	eventListener();
}


GameDisplay::GameDisplay(std::string gameKey) : checkerInHand(NULL), fieldedCheckers(NULL)
{
	gameTick = 0;
	window.create(sf::VideoMode(800, 800), "Checkers!");
	window.setVerticalSyncEnabled(true);
	backgroundTexture.loadFromFile("draughts_board.png");
	background = sf::Sprite(backgroundTexture);
	game = new Game(gameKey);
	updateFieldedCheckers();
	eventListener();
}

// Destructor

GameDisplay::~GameDisplay()
{
	if (fieldedCheckers) delete[] fieldedCheckers;
}

// Driver

void GameDisplay::eventListener()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			gameTick++;
			if (game->isFinished()) {
				std::cout << "DONE!" << endl;
				window.close();
				break;
			}
			switch (event.type)
			{

			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				onMouseMove(event.mouseMove.y, event.mouseMove.x);
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{

				case sf::Mouse::Left:
					onLeftClick(event.mouseButton.y, event.mouseButton.x);
					cout << game->getStatus() << endl;
					break;

				case sf::Mouse::Right:
					game->printBoard();
					break;

				}
				break;

			case sf::Event::MouseButtonReleased:
				switch (event.mouseButton.button)
				{

				case sf::Mouse::Left:
					onLeftRelease(event.mouseButton.y, event.mouseButton.x);
					cout << game->getStatus() << endl;
					break;

				case sf::Mouse::Right:
					break;

				}
				break;

			}
		}
		drawAssets();
	}
}

// Manipulator

void GameDisplay::drawAssets()
{
	// Refresh display on screen

	window.clear();
	window.draw(background);
	if (fieldedCheckers)
	{
		int numberElements = game->getNumberOfAvailableCheckers();
		for (int i = 0; i < numberElements; i++)
		{
			window.draw(*fieldedCheckers[i]->getSprite());
		}
	}
	if (checkerInHand)
	{
		window.draw(*checkerInHand->getSprite());
	}
	window.display();
}


void GameDisplay::onLeftClick(int y, int x)
{ 
	int numberElements = game->getNumberOfAvailableCheckers();
	for (int i = 0; i < numberElements; i++)
	{
		if (fieldedCheckers[i]->getSprite()->getGlobalBounds().contains(static_cast<float>(x), static_cast<float>(y)))
		{
			cout << "Found Checker at " << x << "," << y;
			if (game->selectChecker(fieldedCheckers[i]))
			{
				cout << " This Checker was a valid Selection.";
				checkerInHand = fieldedCheckers[i];
				relativeX = (checkerInHand->getSprite()->getPosition().x - event.mouseButton.x);
				relativeY = (checkerInHand->getSprite()->getPosition().y - event.mouseButton.y);
				cout << endl;
				break;
			}
		}
	}
}


void GameDisplay::onLeftRelease(int y, int x)
{
	if (checkerInHand)
	{
		game->placeChecker(pixToPos(y), pixToPos(x));
		checkerInHand->getSprite()->setPosition(posToPix(checkerInHand->getColumn()), posToPix(checkerInHand->getRow()));
	}
	checkerInHand = nullptr;
	updateFieldedCheckers();
}


void GameDisplay::onMouseMove(int y, int x)
{
	if (checkerInHand && ((gameTick % 3) == 0))
	{
		if ((y > 0) && (y < window.getSize().y) && (x > 0) && (x < window.getSize().x))
		{
			checkerInHand->getSprite()->setPosition(event.mouseMove.x + relativeX, event.mouseMove.y + relativeY);
		}
	}
}


void GameDisplay::updateFieldedCheckers()
{
	// Refresh checkers displayed on the field

	if (game)
	{
		if (fieldedCheckers)
		{
			delete[] fieldedCheckers;
		}
		fieldedCheckers = game->getAvailableCheckers();
		int numberElements = game->getNumberOfAvailableCheckers();
		for (int i = 0; i < numberElements; i++)
		{
			fieldedCheckers[i]->alignSprite(100);
		}
	}
}

// Utility

int GameDisplay::pixToPos(int pixel)
{
	// Relative to board, return position given pixel

	return (pixel / 100);
}


int GameDisplay::pixToPos(float pixel)
{
	// Relative to board, return position given pixel

	return static_cast<int>(pixel / 100);
}


float GameDisplay::posToPix(int position)
{
	// Relative to board, return pixel given position

	return static_cast<float>(position * 100);
}