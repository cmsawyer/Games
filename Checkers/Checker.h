// Checker.h

#pragma once

#ifndef CHECKER_H
#define CHECKER_H

class Checker
{
public:
	// Constructors
	Checker();
	Checker(bool);
	Checker(bool, int, int);
	Checker(const Checker &);

	// Setter Getter pairs
	void setRow(int);
	int getRow() const;
	void setColumn(int);
	int getColumn() const;
	void setAvailable(bool);
	bool isAvailable() const;
	void setPossibleHops(int);
	int getPossibleHops() const;
	void setPossibleSlides(int);
	int getPossibleSlides() const;
	void setSprite(std::string);
	sf::Sprite* getSprite();
	bool isKing() const;
	bool isWhiteTeam() const;

	// Utility
	void removeFromGame();
	void alignSprite(int);
	virtual bool canSlideTo(int, int) const;
	virtual bool canHopTo(int, int) const;


private:
	// Modifiable Data Members
	int row;
	int column;
	bool available;
	int possibleHops;
	int possibleSlides;
	sf::Sprite sprite;
	sf::Texture texture;

	// Constructed Data Members
	bool king;
	bool whiteTeam;


protected:
	// Extended Setter
	void setKing(bool);
};

#endif