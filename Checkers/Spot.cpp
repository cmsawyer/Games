#include "stdafx.h"
#include "Spot.h"

// Constructors

Spot::Spot() : checker(NULL)
{
}


Spot::Spot(int row, int column) : checker(NULL)
{
	this->row = row;
	this->column = column;
}

// Setter / Modifiers

Checker* Spot::popChecker()
{
	// Remove and return the Checker on this Spot

	Checker* temp;
	if (hasChecker())
	{
		temp = checker;
		checker = nullptr;
		return temp;
	}
	return nullptr;
}


void Spot::pushChecker(Checker* checker)
{
	// Set the a passed Checker on this Spot

	if (hasChecker() == false)
	{
		checker->setRow(getRow());
		checker->setColumn(getColumn());
		this->checker = checker;
	}
}

// Getters

Checker* const Spot::peekChecker() const
{
	// Read but not Write to the Checker on this Spot

	if (hasChecker())
	{
		return checker;
	}
	return nullptr;
}


int Spot::getRow() const
{
	return row;
}


int Spot::getColumn() const
{
	return column;
}


bool Spot::hasChecker() const
{
	// Is this currently holding a checker

	if (checker)
	{
		return true;
	}
	return false;
}


bool Spot::isAvailable() const
{
	// Is playable Spot

	if ((((getColumn() % 2) == 0) && ((getRow() % 2) == 1)) 
		|| (((getColumn() % 2) == 1) && ((getRow() % 2) == 0)))
	{
		return true;
	}
	return false;
}