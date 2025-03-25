#pragma once
#include "Card.h"
class MonopolyCards : public Card
{
public:
	MonopolyCards(const CellPosition& pos);
	int ReadCardPrice(Grid* pGrid);
	int ReadCardFees(Grid* pGrid);
	virtual bool TakesParameters() const;
};