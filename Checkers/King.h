// King.h

#pragma once

#ifndef KING_H
#define KING_H

#include "Checker.h"

class King : public Checker
{
public:
	// Constructors
	King();
	King(bool);
	King(bool, int, int);
	King(const Checker &);

	// Utility Overridden from Checker
	bool canSlideTo(int, int) const override;
	bool canHopTo(int, int) const override;

};

#endif