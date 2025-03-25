#include "CardSix.h"
#include <fstream>

CardSix::CardSix(const CellPosition& pos) : Card(pos) {
	cardNumber = 6; // set the inherited cardNumber data member with the card number (6 here)
}

void CardSix::Apply(Grid* pGrid, Player* pPlayer) {
	Card::Apply(pGrid, pPlayer);
	int currCellNum = position.GetCellNumFromPosition(position);
	pGrid->UpdatePlayerCell(pPlayer, CellPosition::GetCellPositionFromNum(currCellNum - pPlayer->GetJustRolledDiceNumber()));
}

Card* CardSix::CopyCard(CellPosition& pos)
{
	return new CardSix(pos);
}

void CardSix::save(ofstream& output)
{
	Card::save(output);
	output << endl;
}

CardSix:: ~CardSix() {}