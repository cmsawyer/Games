// Game.h

#pragma once

#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Spot.h"
#include "Team.h"
#include "Checker.h"
#include "King.h"

class Game
{
public:
	// Constructors
	Game();
	Game(std::string);

	// Destructor
	~Game();

	// Getters
	void setStatus(std::string);
	std::string getStatus() const;
	std::string getGameKey();
	int possibleHops(Checker*) const;
	int possibleSlides(Checker*) const;
	bool isWhiteTurn() const;
	bool isFinished() const;
	bool mayHopTo(Checker*, Spot*) const;
	bool maySlideTo(Checker*, Spot*) const;
	Checker** const getAvailableCheckers() const;
	int getNumberOfAvailableCheckers() const;

	// Manipulators
	bool selectChecker(Checker*);
	bool selectChecker(int, int);
	void placeChecker(int, int);
	void nextTurn();

	// Utility
	void printBoard() const;


private:
	// Data Members
	Team * teams;
	Team * curTeam;
	Board board;
	Spot * prevSpot;
	Checker * heldChecker;
	std::string status;
	std::string gameKey = "01212!\"#$%&'()*+,UVWXYZ[\\]^_`";
	bool whiteTurn;

	// Manipulators
	void updateGameKey();
	void updatePossibleMoves();
	void updateKings();

	// Initializer
	void initializeGame(std::string);

	// Utility
	char checkerToChar(Checker*);
	Checker* charToChecker(char);

};

#endif