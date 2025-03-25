#include "CardThree.h"
#include <fstream>

CardThree::CardThree(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
}

void CardThree::ReadCardParameters(Grid* pGrid)
{

}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pGrid->PrintErrorMessage("This card moves you to the beginning of the next ladder. Click to continue...");

	Ladder* next_ladder = pGrid->GetNextLadder(this->GetPosition());

	if (!next_ladder)
	{
		pGrid->PrintErrorMessage("There is no ladder ahead of you! Click to continue...");
	}
	else {
		pGrid->UpdatePlayerCell(pPlayer, next_ladder->GetPosition());
		next_ladder->Apply(pGrid, pPlayer);
	}
}

Card* CardThree::CopyCard(CellPosition& pos)
{
	return new CardThree(pos);
}

void CardThree::save(ofstream& output) {
	Card::save(output);
	output << endl;
}


CardThree::~CardThree()
{
}