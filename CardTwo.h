#pragma once
#include "Card.h"
//  Functionality :: Increments the passing player’s wallet by a value specified when adding the card
//                   to the grid in the design mode.
//  Input         :: Value to be added to the passing players’ wallets.
class CardTwo : public Card
{
	int AddedValue;
public :
	CardTwo(const CellPosition& Cell_Pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual bool UserInputValidation();
	virtual bool TakesParameters() const;
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	virtual Card* CopyCard(CellPosition& pos);
	virtual bool EditParameters(Grid* pGrid);
	virtual void save(ofstream& output);
	virtual void load(ifstream& input);
	virtual ~CardTwo();


};

