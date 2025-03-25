#pragma once
#include "Card.h"
#include"snake.h"

/*
Card4:
 ● Moves the player forward to the start of the next snake. (If no snakes ahead, do
 nothing)
 ● Input data: None.
*/

class CardFour : public Card
{

public:
	CardFour(const CellPosition& pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid* pGrid); // Reads nothing

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFour on the passed Player
	// by moving the player to the next snake and apply the snake;
	virtual Card* CopyCard(CellPosition& pos);
	void save(ofstream& output);
	virtual ~CardFour(); // A Virtual Destructor
};