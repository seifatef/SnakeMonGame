#pragma once
#include"Card.h"

/*
Card6:
 ● Movesthe player backward by the same number of steps that he just rolled.
 ● Input data: None.
*/

class CardSix :public Card
{
public:
	CardSix(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFour on the passed Player.
	// By Moving backward by the same number of steps that you just rolled and moved already.
	virtual Card* CopyCard(CellPosition& pos);
	void save(ofstream& output);

	virtual ~CardSix(); // A Virtual Destructor
};