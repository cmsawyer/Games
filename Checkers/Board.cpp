// Board.cpp

#include "stdafx.h"
#include "Board.h"

// Constructors

Board::Board() : spots(NULL)
{
}


Board::Board(int dim)
{
	// Set Data Members
	this->rows = dim;
	this->columns = dim;

	// Allocate Data
	initializeSpots();
}


Board::Board(int rows, int columns)
{
	// Set Data Members
	this->rows = rows;
	this->columns = columns;

	// Allocate Data
	initializeSpots();
}

// Destructor

Board::~Board()
{
	// Free allocated space given to Spot objects

	if (spots)
	{
		delete[] spots;
	}
}

// Getters

int Board::getRows() const
{
	return rows;
}


int Board::getColumns() const
{
	return columns;
}


int Board::getNumberOfAvailableSpots() const
{
	// Tally and return number of available spots

	int count = 0;
	for (int row = 0; row < getRows(); row++)
	{
		for (int column = 0; column < getColumns(); column++)
		{
			if (getSpot(row, column)->isAvailable() == true)
			{
				count++;
			}
		}
	}
	return count;
}


Spot* Board::getSpot(int row, int column) const
{
	// Return spot at specified coordinates

	if ((row >= 0) && (row < getRows()) && (column >= 0) && (column < getColumns()))
	{
		return &spots[row * getRows() + column];
	}
	return nullptr;
}


Spot* Board::getSpotBetween(Spot* start, Spot* finish) const
{
	// Return spot lying underneath a hop between any two spots of distance 2

	int row = ((start->getRow() + finish->getRow()) / 2);
	int column = ((start->getColumn() + finish->getColumn()) / 2);
	if ((2 == abs(start->getRow() - finish->getRow())) 
		&& (2 == abs(start->getColumn() - finish->getColumn())))
	{
		return getSpot(row, column);
	}
	return nullptr;
}


void Board::initializeSpots()
{
	// Dynamically Allocate memory for the storage of Spot objects

	spots = new Spot[getRows() * getColumns()];
	for (int row = 0; row < getRows(); row++)
	{
		for (int column = 0; column < getColumns(); column++)
		{
			spots[row * getRows() + column] = *new Spot(row, column);
		}
	}
}