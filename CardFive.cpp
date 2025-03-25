#include "CardFive.h"
#include <fstream>
CardFive::CardFive(const CellPosition& pos) : Card(pos) {
	cardNumber = 5; // set the inherited cardNumber data member with the card number (5 here)
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer) {
	Card::Apply(pGrid, pPlayer);
	int currCellNum = position.GetCellNumFromPosition(position);
	pGrid->UpdatePlayerCell(pPlayer, CellPosition::GetCellPositionFromNum(currCellNum + pPlayer->GetJustRolledDiceNumber()));
}

Card* CardFive::CopyCard(CellPosition& pos)
{
	return new CardFive(pos);
}

void CardFive::save(ofstream& output)
{
	Card::save(output);
	output << endl;
}

CardFive:: ~CardFive() {}