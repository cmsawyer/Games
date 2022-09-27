// Spot.h

#pragma once

#ifndef SPOT_H
#define SPOT_H

#include "Checker.h"

class Spot
{
public:
	// Constructors
	Spot();
	Spot(int, int);

	// Setter / Modifiers
	Checker* popChecker();
	void pushChecker(Checker*);

	// Getters
	Checker* const peekChecker() const;
	int getRow() const;
	int getColumn() const;
	bool hasChecker() const;
	bool isAvailable() const;


private:
	// Data Members
	int row;
	int column;
	Checker* checker;
};

#endif