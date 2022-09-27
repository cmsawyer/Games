// Team.cpp

#include "stdafx.h"
#include "Team.h"

// Constructors

Team::Team() : checkers(NULL)
{
}


Team::Team(int numberOfCheckers, bool whiteTeam)
{
	// Set Data Members
	this->numberOfCheckers = numberOfCheckers;
	this->whiteTeam = whiteTeam;
	if (isWhiteTeam())
	{
		this->teamName = "White Team";
	}
	else
	{
		this->teamName = "Red Team";
	}

	// Allocate Memory for Data Member
	initializeCheckers();
}

// Destructor

Team::~Team()
{
	// Frees allocated memory from array 'checkers'

	if (checkers)
	{
		for (int i = 0; i < getNumberOfCheckers(); i++)
		{
			if (checkers[i])
			{
				delete checkers[i];
			}
		}
		delete[] checkers;
	}
}

// Getters

bool Team::isWhiteTeam() const
{
	return whiteTeam;
}


std::string Team::getTeamName() const
{
	return teamName;
}


Checker* Team::getChecker(int checker) const
{
	// Returns specified checker

	if ((checker >= 0) && (checker < getNumberOfCheckers()))
	{
		return checkers[checker];
	}
	return nullptr;
}


int Team::getNumberOfCheckers() const
{
	return numberOfCheckers;
}


Checker** const Team::getAvailableCheckers() const
{
	// Return Read-only list of available Checkers for this player
	// Must be deleted by calling function

	int index = 0;
	Checker** availableCheckers = new Checker*[getNumberOfAvailableCheckers()];
	for (int i = 0; i < getNumberOfCheckers(); i++)
	{
		if (getChecker(i)->isAvailable())
		{
			availableCheckers[index] = getChecker(i);
			index++;
		}
	}
	return availableCheckers;
}


int Team::getNumberOfAvailableHops() const
{
	// Tallies total number of 'possibleHops' for all checkers

	int count = 0;
	for (int i = 0; i < getNumberOfCheckers(); i++)
	{
		if (getChecker(i)->isAvailable())
		{
			count += getChecker(i)->getPossibleHops();
		}
	}
	return count;
}


int Team::getNumberOfAvailableSlides() const
{
	// Tallies total number of 'possibleSlides' for all checkers

	int count = 0;
	for (int i = 0; i < getNumberOfCheckers(); i++)
	{
		if (getChecker(i)->isAvailable())
		{
			count += getChecker(i)->getPossibleSlides();
		}
	}
	return count;
}


int Team::getNumberOfAvailableCheckers() const
{
	// Tallies total number of 'available' checkers

	int count = 0;
	for (int i = 0; i < getNumberOfCheckers(); i++)
	{
		if (checkers[i]->isAvailable())
		{
			count++;
		}
	}
	return count;
}

// Manipulator

void Team::kingChecker(int index)
{
	// Replaces designated Checker with King of same values

	if ((index >= 0) && (index < getNumberOfCheckers()))
	{
		const Checker temp = *checkers[index];
		delete checkers[index];
		checkers[index] = new King(temp);
	}
}

// Private Initializer

void Team::initializeCheckers()
{
	// Dynamically allocate memory for Checker storage. Arrays of Pointers allow
	// Polymorhpism in th object type. E.g: You can store a King in this array

	checkers = new Checker*[getNumberOfCheckers()];
	for (int i = 0; i < getNumberOfCheckers(); i++)
	{
		checkers[i] = new Checker(isWhiteTeam());
	}
}