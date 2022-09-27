// Board.h

#pragma once

#ifndef BOARD_H
#define BOARD_H

#include "Spot.h"

class Board
{
public:
	// Constructors
	Board();
	Board(int);
	Board(int, int);

	// Destructor
	~Board();

	// Getters
	int getRows() const;
	int getColumns() const;
	int getNumberOfAvailableSpots() const;
	Spot* getSpot(int, int) const;
	Spot* getSpotBetween(Spot*, Spot*) const;


private:
	// Data Members
	int rows;
	int columns;
	Spot* spots;

	// Private Initializer
	void initializeSpots();

};

#endif