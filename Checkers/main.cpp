#include "stdafx.h"
#include "GameDisplay.h"

int main()
{
	GameDisplay* checkers = new GameDisplay();
	delete checkers;
	return 0;
}

/*
TODO:
- Add double hops
- Optimize isFinished() check
- Check for more bugs
*/