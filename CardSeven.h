#pragma once
#include "Card.h"

/*
 Card7:
 ● Gives the player another dice roll.
 ● Input data: None.
*/

class CardSeven : public Card
{
	//No card parameters

public:
	CardSeven(const CellPosition&); // A Constructor takes card position

	virtual void ReadCardParameters(Grid*); // Reads nothing

	virtual void Apply(Grid*, Player*); //Applies the effect of CardThree on passed player
	//by giving passed player another dice roll  
	virtual Card* CopyCard(CellPosition& pos);
	void save(ofstream& output);

	virtual ~CardSeven(); // A Virtual Destructor
};
