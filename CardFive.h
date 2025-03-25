#pragma once
#include"Card.h"

/*
Card5:
 ● Move forward by the same number of steps that you just rolled and moved
 already. (if you reach a ladder or a snake at the end of moving forward, take it).
 ● Input data: None.
*/

class CardFive :public Card
{
public:
	CardFive(const CellPosition& pos); // A Constructor takes card position

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFour on the passed Player.
	// By Moving forward by the same number of steps that you just rolled and moved already.
	virtual Card* CopyCard(CellPosition& pos);
	void save(ofstream& output);
	virtual ~CardFive(); // A Virtual Destructor
};