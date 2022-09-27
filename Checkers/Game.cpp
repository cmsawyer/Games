#include "stdafx.h"
#include "Game.h"

using namespace std;

Game::Game() : heldChecker(NULL), prevSpot(NULL)
{
	teams = new Team[2];
	teams[0] = *new Team(12, false);
	teams[1] = *new Team(12, true);
	board = *new Board(8);
	initializeGame(gameKey);
	setStatus("New Game! " + curTeam->getTeamName() + "'s turn!");
}


Game::Game(string gameKey) : heldChecker(NULL), prevSpot(NULL)
{
	teams = new Team[2];
	teams[0] = *new Team(12, false);
	teams[1] = *new Team(12, true);
	board = *new Board(8);
	initializeGame(gameKey);
}


Game::~Game()
{
	if (teams)
	{
		delete[] teams;
	}
}


void Game::setStatus(string status)
{
	this->status = status;
}


string Game::getStatus() const
{
	return status;
}


string Game::getGameKey()
{
	return gameKey;
}


bool Game::isWhiteTurn() const
{
	if (curTeam->isWhiteTeam())
	{
		return true;
	}
	return false;
}


bool Game::isFinished() const
{
	if ((teams[0].getNumberOfAvailableCheckers() == 0) || teams[1].getNumberOfAvailableCheckers() == 0)
	{
		return true;
	}
	return false;
}


void Game::nextTurn()
{
	if (isWhiteTurn())
	{
		curTeam = &teams[0];
	}
	else
	{
		curTeam = &teams[1];
	}
	updatePossibleMoves();
	updateGameKey();
	setStatus(curTeam->getTeamName() + "'s turn!");
}


void Game::printBoard() const
{
	cout << "  0 1 2 3 4 5 6 7";
	for (int row = 0; row < board.getRows(); row++)
	{
		cout << "\n" << row;
		for (int column = 0; column < board.getColumns(); column++)
		{
			if (board.getSpot(row, column)->isAvailable())
			{
				if (board.getSpot(row, column)->hasChecker())
				{
					if (board.getSpot(row, column)->peekChecker()->isKing())
					{
						cout << "*";
					}
					else
					{
						cout << " ";
					}
					if (board.getSpot(row, column)->peekChecker()->isWhiteTeam())
					{
						cout << "W";
					}
					else
					{
						cout << "R";
					}
				}
				else
				{
					cout << " -";
				}
			}
			else
			{
				cout << " .";
			}
		}
	}
	cout << endl;
}


bool Game::mayHopTo(Checker* checker, Spot* spot) const
{
	if (spot->isAvailable() && (spot->hasChecker() == false))
	{
		if (checker->canHopTo(spot->getRow(), spot->getColumn()))
		{
			if (board.getSpotBetween(board.getSpot(checker->getRow(), checker->getColumn()), spot)->hasChecker())
			{
				if (board.getSpotBetween(board.getSpot(checker->getRow(), checker->getColumn()), spot)->peekChecker()->isWhiteTeam() != checker->isWhiteTeam())
					return true;
			}
		}
	}
	return false;
}


bool Game::maySlideTo(Checker* checker, Spot* spot) const
{
	if (spot->isAvailable() && (spot->hasChecker() == false))
	{
		if (checker->canSlideTo(spot->getRow(), spot->getColumn()))
		{
			return true;
		}
	}
	return false;
}


int Game::possibleHops(Checker* checker) const
{
	int count = 0;
	Spot* curSpot;
	for (int row = 0; row < board.getRows(); row++)
	{
		for (int column = 0; column < board.getColumns(); column++)
		{
			curSpot = board.getSpot(row, column);
			if (mayHopTo(checker, curSpot))
			{
				count++;
			}
		}
	}
	checker->setPossibleHops(count);
	return count;
}


int Game::possibleSlides(Checker* checker) const
{
	int count = 0;
	Spot* curSpot;
	for (int row = 0; row < board.getRows(); row++)
	{
		for (int column = 0; column < board.getColumns(); column++)
		{
			curSpot = board.getSpot(row, column);
			if (maySlideTo(checker, curSpot))
			{
				count++;
			}
		}
	}
	checker->setPossibleSlides(count);
	return count;
}


void Game::updatePossibleMoves()
{
	for (int i = 0; i < curTeam->getNumberOfCheckers(); i++)
	{
		possibleHops(curTeam->getChecker(i));
		possibleSlides(curTeam->getChecker(i));
	}
}


Checker** const Game::getAvailableCheckers() const
{
	// Return a Read-Only list of Available Checkers from both teams
	int team0Available = teams[0].getNumberOfAvailableCheckers();
	int team1Available = teams[1].getNumberOfAvailableCheckers();
	int numberOf = (team0Available + team1Available);
	Checker** availableCheckers = new Checker*[numberOf];
	Checker** redCheckers = teams[0].getAvailableCheckers();
	Checker** whiteCheckers = teams[1].getAvailableCheckers();
	for (int i = 0; i < numberOf; i++)
	{
		if (i < team0Available)
		{
			availableCheckers[i] = redCheckers[i];
		}
		else
		{
			availableCheckers[i] = whiteCheckers[i - team0Available];
		}
	}
	delete[] redCheckers;
	delete[] whiteCheckers;
	return availableCheckers;
}


int Game::getNumberOfAvailableCheckers() const
{
	return (teams[0].getNumberOfAvailableCheckers() + teams[1].getNumberOfAvailableCheckers());
}


bool Game::selectChecker(Checker* checker)
{
	// Converts and calls selectChecker(int, int);

	int row = checker->getRow();
	int column = checker->getColumn();
	return selectChecker(row, column);
}


bool Game::selectChecker(int row, int column)
{
	// Save previous position
	prevSpot = board.getSpot(row, column);

	if (prevSpot && prevSpot->isAvailable() && prevSpot->hasChecker())
	{
		Checker* checker = prevSpot->popChecker();
		// Verify Selection
		if (checker->isAvailable() && (checker->isWhiteTeam() == curTeam->isWhiteTeam()))
		{
			// Prioritize Hops
			if (curTeam->getNumberOfAvailableHops() > 0)
			{
				// Player has hops and this checker is valid
				if (checker->getPossibleHops() > 0)
				{
					setStatus("Holding Checker at " + to_string(checker->getColumn()) + "," + to_string(checker->getRow()) + ". ");
					heldChecker = checker;
					return true;
				}
				// This has no hops, but a checker with hops exists
				else
				{
					setStatus("A Checker with Hops exists! ");
					prevSpot->pushChecker(checker);
					return false;
				}
			}
			// Then Slides
			else if (curTeam->getNumberOfAvailableSlides() > 0)
			{
				// Player has possible slides, and the checker is valid
				if (checker->getPossibleSlides() > 0)
				{
					setStatus("Holding Checker at " + to_string(checker->getColumn()) + "," + to_string(checker->getRow()) + ". ");
					heldChecker = checker;
					return true;
				}
				else
				{
					setStatus("This Checker has no moves. Select another! ");
					prevSpot->pushChecker(checker);
					return false;
				}
			}
			// Player has no moves
			else
			{
				setStatus("You have no valid moves! ");
				prevSpot->pushChecker(checker);
				nextTurn(); // FIXME : This player should lose, it shouldn't switch turns
				return false;
			}
		}
		prevSpot->pushChecker(checker);
	}
	heldChecker = nullptr;
	return false;
}


/*Checker* Game::selectCheckerAt(int row, int column)
{
	// If a checker with hops exists. This player must select then hop with one of those available Checkers.
	prevSpot = board.getSpot(row, column);
	if (prevSpot && prevSpot->isAvailable() && prevSpot->hasChecker())
	{
		if (prevSpot->peekChecker()->isAvailable() && prevSpot->peekChecker()->isWhiteTeam() == this->whiteTurn)
		{
			if (curTeam->getNumberOfAvailableHops() > 0)
			{
				if (prevSpot->peekChecker()->getPossibleHops() > 0)
				{
					heldChecker = prevSpot->popChecker();
					setStatus("Selected Checker at " + to_string(column) + "," + to_string(row));
					return heldChecker;
				}
				else
				{
					setStatus("Cannot Select. A Checker with hops exists!");
					return nullptr;
				}
			}
			else // Add getPossibleSlides()?
			{
				heldChecker = prevSpot->popChecker();
				setStatus("Selected Checker at " + to_string(column) + "," + to_string(row));
				return heldChecker;
			}
		}
	}
	setStatus("Invalid Selection!");
	return nullptr;
}*/


void Game::placeChecker(int row, int column)
{
	Spot* newSpot = board.getSpot(row, column);
	if (newSpot && heldChecker)
	{
		if (heldChecker->getPossibleHops() > 0)
		{
			if (mayHopTo(heldChecker, newSpot))
			{
				newSpot->pushChecker(heldChecker);
				board.getSpotBetween(prevSpot, newSpot)->popChecker()->removeFromGame();
				heldChecker = nullptr;
				prevSpot = nullptr;
				setStatus("Hopped Checker to " + to_string(column) + "," + to_string(row));
				updateKings();
				nextTurn();
				return;
			}
			else
			{
				setStatus("Invalid Move! A possible Hop exists for this Checker.");
			}
		}
		else if (maySlideTo(heldChecker, newSpot))
		{
			newSpot->pushChecker(heldChecker);
			heldChecker = nullptr;
			prevSpot = nullptr;
			setStatus("Slid Checker to " + to_string(column) + "," + to_string(row));
			updateKings();
			nextTurn();
			return;
		}
		else
		{
			setStatus("Invalid Move!");
		}
	}
	prevSpot->pushChecker(heldChecker);
	heldChecker = nullptr;
	prevSpot = nullptr;
}


void Game::updateKings()
{
	int kingRow = 0;
	if (curTeam->isWhiteTeam() == false)
	{
		kingRow = (board.getRows() - 1);
	}
	for (int i = 0; i < curTeam->getNumberOfCheckers(); i++)
	{
		if ((curTeam->getChecker(i)->getRow() == kingRow) && (curTeam->getChecker(i)->isKing() == false))
		{
			board.getSpot(curTeam->getChecker(i)->getRow(), curTeam->getChecker(i)->getColumn())->popChecker();
			curTeam->kingChecker(i);
			board.getSpot(curTeam->getChecker(i)->getRow(), curTeam->getChecker(i)->getColumn())->pushChecker(curTeam->getChecker(i));
			setStatus("Kinged Checker at " + to_string(curTeam->getChecker(i)->getColumn()) + "," + to_string(curTeam->getChecker(i)->getRow()));
		}
	}
}


void Game::initializeGame(std::string gameKey)
{
	string::size_type sz;
	int num = stoi(gameKey, &sz);
	int team = (num / 10000);
	curTeam = &teams[team];
	int redCheckers = (num / 100);
	int totalCheckers = (redCheckers + num - (redCheckers * 100));
	int row, column;
	gameKey = gameKey.substr(sz);
	for (int i = 0; i < totalCheckers; i++)
	{
		if (i < redCheckers)
		{
			*teams[0].getChecker(i) = *charToChecker(gameKey.at(i));
			if (teams[0].getChecker(i)->isKing())
			{
				teams[0].kingChecker(i);
			}
			row = teams[0].getChecker(i)->getRow();
			column = teams[0].getChecker(i)->getColumn();
			board.getSpot(row, column)->pushChecker(teams[0].getChecker(i));
		}
		else
		{
			int iOffset = (i - redCheckers);
			*teams[1].getChecker(iOffset) = *charToChecker(gameKey.at(i));
			if (teams[1].getChecker(iOffset)->isKing())
			{
				teams[1].kingChecker(iOffset);
			}
			row = teams[1].getChecker(iOffset)->getRow();
			column = teams[1].getChecker(iOffset)->getColumn();
			board.getSpot(row, column)->pushChecker(teams[1].getChecker(iOffset));
		}
	}
	updatePossibleMoves();
	return;
}


void Game::updateGameKey()
{
	if (curTeam == &teams[0])
	{
		gameKey = to_string(0);
	}
	else
	{
		gameKey = to_string(1);
	}
	gameKey += to_string(teams[0].getNumberOfAvailableCheckers());
	gameKey += to_string(teams[1].getNumberOfAvailableCheckers());
	for (int i = 0; i < (teams[0].getNumberOfCheckers() + teams[1].getNumberOfCheckers()); i++)
	{
		if (i < teams[0].getNumberOfCheckers())
		{
			if (teams[0].getChecker(i)->isAvailable())
			{
				gameKey += checkerToChar(teams[0].getChecker(i));
			}
		}
		else
		{
			if (teams[1].getChecker(i - teams[0].getNumberOfCheckers())->isAvailable())
			{
				gameKey += checkerToChar(teams[1].getChecker(i - teams[0].getNumberOfCheckers()));
			}
		}
	}
}


char Game::checkerToChar(Checker* checker)
{
	// Encode Checker data as a single char

	// Get position
	int row = checker->getRow();
	int column = checker->getColumn();
	// Concatenate into one number
	row *= 10;
	int num = (column + row);
	// Adjust to linear count based on position
	num -= ((row / 10) * 2);
	if (num % 2 == 1) num--;
	num /= 2;
	// Encode team
	if (checker->isWhiteTeam()) num += 32;
	// Encode type
	if (checker->isKing()) num += 65;
	// Avoid character 127
	if (num >= 127) num++;
	// Return printable characters
	return static_cast<char>(num + 33);
}


Checker* Game::charToChecker(char c)
{
	// Decypher a char to a specific Checker

	// Initialize local members
	bool king = false;
	bool white = false;
	// Cast char to int
	int code = static_cast<int>(c);
	// Adjust to all characters
	code -= 33;
	// Include code 127
	if (code > 127) code--;
	// Read king
	if (code >= 65)
	{
		king = true;
		code -= 65;
	}
	// Read white team
	if (code >= 32)
	{
		white = true;
		code -= 32;
	}
	// Decypher row
	int row = (code / 4);
	// Adjust to concatenated position digit
	code *= 2;
	code += (row * 2);
	if (row % 2 == 0) code++;
	// Decypher column
	int column = (code - (row * 10));
	// Return appropriate type/team
	if (king) return new King(white, row, column);
	return new Checker(white, row, column);
}