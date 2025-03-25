#pragma once
#include "Card.h"
// Functionality ::  Prevents the player from rolling the next turn... giving a zero value to the dice...
//                   the game works normally after that as the turn counts.
//Inputs         ::  None 
class CardEight : public Card
{

public :
	CardEight(const CellPosition& Cell_Pos );
	virtual void ReadCardParameters(Grid* pGrid); //reads nothing as no parametres
	virtual void Apply(Grid* pGrid, Player* pPlayer); //Apply the Functionality 
	virtual Card* CopyCard(CellPosition& pos);
	void save(ofstream& output);
	virtual ~CardEight(); // to ensure the bestpractice use with pointers 

};

