// Checker.cpp

#include "stdafx.h"
#include "Checker.h"

// Constructors

Checker::Checker()
{
	// Setters
	setRow(-1);
	setColumn(-1);
	setAvailable(false);
	setPossibleHops(0);

	// Initializer
	setKing(false);
}


Checker::Checker(bool whiteTeam)
{
	// Setters
	setRow(-1);
	setColumn(-1);
	setAvailable(false);
	setPossibleHops(0);

	// Initializer
	setKing(false);
	this->whiteTeam = whiteTeam;

	// Set this Sprite based on Team	
	if (isWhiteTeam()) setSprite("draughts_whiteChecker.png");
	else setSprite("draughts_redChecker.png");
}


Checker::Checker(bool whiteTeam, int row, int column)
{
	// Setters
	setRow(row);
	setColumn(column);
	setAvailable(true);
	setPossibleHops(0);

	// Initializer
	setKing(false);
	this->whiteTeam = whiteTeam;

	// Set this Sprite based on Team	
	if (isWhiteTeam()) setSprite("draughts_whiteChecker.png");
	else setSprite("draughts_redChecker.png");
}


Checker::Checker(const Checker &checker)
{
	// Setters
	setRow(checker.getRow());
	setColumn(checker.getColumn());
	setAvailable(checker.isAvailable());
	setPossibleHops(checker.getPossibleHops());

	// Initializer
	setKing(checker.isKing());
	this->whiteTeam = checker.isWhiteTeam();

	// Set this Sprite based on Team	
	if (checker.isWhiteTeam()) setSprite("draughts_whiteChecker.png");
	else setSprite("draughts_redChecker.png");
}

// Setter / Getter Pairs

void Checker::setRow(int row)
{
	this->row = row;
}


int Checker::getRow() const
{
	return row;
}


void Checker::setColumn(int column)
{
	this->column = column;
}


int Checker::getColumn() const
{
	return column;
}


void Checker::removeFromGame()
{
	setRow(-1);
	setColumn(-1);
	setAvailable(false);
	getSprite()->setPosition(-100, -100);
}


void Checker::alignSprite(int spotSize)
{
	float pixelX = static_cast<float>(getColumn() * spotSize);
	float pixelY = static_cast<float>(getRow() * spotSize);
	getSprite()->setPosition(pixelX, pixelY);
}


void Checker::setAvailable(bool available)
{
	this->available = available;
}


bool Checker::isAvailable() const
{
	return available;
}


void Checker::setPossibleHops(int possibleHops)
{
	this->possibleHops = possibleHops;
}


int Checker::getPossibleHops() const
{
	return possibleHops;
}


void Checker::setPossibleSlides(int possibleSlides)
{
	this->possibleSlides = possibleSlides;
}


int Checker::getPossibleSlides() const
{
	return possibleSlides;
}


void Checker::setSprite(std::string path)
{
	texture.loadFromFile(path);
	sprite = sf::Sprite(texture);
}


sf::Sprite* Checker::getSprite()
{
	return &sprite;
}

// Getters with No Setters

bool Checker::isWhiteTeam() const
{
	return this->whiteTeam;
}


bool Checker::isKing() const
{
	return this->king;
}

// Protected Initializer

void Checker::setKing(bool king)
{
	this->king = king;
}

// Utility used for Logic

bool Checker::canSlideTo(int destRow, int destColumn) const
{
	// Given it's current coordinates, can this checker slide to the passed coordinates?

	int dir = 1;
	if (isWhiteTeam()) dir = -1;
	if ((destRow == (getRow() + dir))
		&& ((destColumn == (getColumn() + dir)) || (destColumn == (getColumn() - dir))))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Checker::canHopTo(int destRow, int destColumn) const
{
	// Given it's current coordinates, can this checker hop to the passed coordinates?

	int dir = 2;
	if (isWhiteTeam()) dir = -2;
	if ((destRow == (getRow() + dir)) 
		&& ((destColumn == (getColumn() + dir)) || (destColumn == (getColumn() - dir))))
	{
		return true;
	}
	else
	{
		return false;
	}
}