#include "CardEight.h"
#include <fstream>

CardEight::CardEight(const CellPosition& Cell_Pos) : Card(Cell_Pos) {
	cardNumber = 8; // set the inherited cardNumber data member with the card number (8 here)
}

void CardEight::ReadCardParameters(Grid* pGrid)
{
	// Reads Nothing
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	pGrid->PrintErrorMessage("This card prevents player from rolling next turn. Click to continue...");
	pPlayer->PreventPlaying();
}

Card* CardEight::CopyCard(CellPosition& pos)
{
	return new CardEight(pos);
}

void CardEight::save(ofstream& output)
{
	Card::save(output);
	output << endl;
}

CardEight::~CardEight()
{

}

