// King.cpp

#include "stdafx.h"
#include "King.h"

// Constructors

King::King() : Checker()
{
	setKing(true);
}


King::King(bool whiteTeam) : Checker(whiteTeam)
{
	// Override Checker constructor
	setKing(true);

	// Set this Sprite based on Team	
	if (isWhiteTeam()) setSprite("draughts_whiteKing.png");
	else setSprite("draughts_redKing.png");
}


King::King(bool whiteTeam, int row, int column) : Checker(whiteTeam, row, column)
{
	// Override Checker constructor
	setKing(true);

	// Set this Sprite based on Team	
	if (isWhiteTeam()) setSprite("draughts_whiteKing.png");
	else setSprite("draughts_redKing.png");
}


King::King(const Checker &checker) : Checker(checker)
{
	// Override Checker constructor
	setKing(true);

	// Set this Sprite based on Team	
	if (isWhiteTeam()) setSprite("draughts_whiteKing.png");
	else setSprite("draughts_redKing.png");
}

// Overriden utility used for logic

bool King::canSlideTo(int destRow, int destColumn) const
{
	// Given it's current coordinates, can this king slide to the passed coordinates?

	int dir = 1;
	if (((destRow == (getRow() + dir)) || (destRow == (getRow() - dir)))
		&& ((destColumn == (getColumn() + dir)) || (destColumn == (getColumn() - dir))))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool King::canHopTo(int destRow, int destColumn) const
{
	// Given it's current coordinates, can this king hop to the passed coordinates?

	int dir = 2;
	if (((destRow == (getRow() + dir)) || (destRow == (getRow() - dir)))
		&& ((destColumn == (getColumn() + dir)) || (destColumn == (getColumn() - dir))))
	{
		return true;
	}
	else
	{
		return false;
	}
}