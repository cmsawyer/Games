// Team.h

#pragma once

#ifndef TEAM_H
#define TEAM_H

#include "Checker.h"
#include "King.h"

class Team
{
public:
	// Constructors
	Team();
	Team(int, bool);

	// Destructor
	~Team();

	// Getters
	bool isWhiteTeam() const;
	std::string getTeamName() const;
	int getNumberOfCheckers() const;
	int getNumberOfAvailableHops() const;
	int getNumberOfAvailableSlides() const;
	int getNumberOfAvailableCheckers() const;
	Checker* getChecker(int) const;
	Checker** const getAvailableCheckers() const;

	// Manipulator
	void kingChecker(int);


private:
	// Constructed Data Members
	bool whiteTeam;
	std::string teamName;
	int numberOfCheckers;
	Checker * * checkers;

	// Initializer
	void initializeCheckers();

};

#endif