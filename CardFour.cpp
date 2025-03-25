#include "CardFour.h"
#include "Snake.h"
#include <fstream>
CardFour::CardFour(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (4 here)
}

void CardFour::ReadCardParameters(Grid* pGrid)
{

}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pGrid->PrintErrorMessage("This card moves you to the next snake. Click to continue...");

	Snake* next_snake = pGrid->GetNextSnake(this->GetPosition());
	if (!next_snake)
	{
		pGrid->PrintErrorMessage("There is no snake ahead of you! Click to continue...");
		return;
	}
	else {
		pGrid->UpdatePlayerCell(pPlayer, next_snake->GetPosition());
		next_snake->Apply(pGrid, pPlayer);
	}
}

Card* CardFour::CopyCard(CellPosition& pos)
{
	return new CardFour(pos);
}

void CardFour::save(ofstream& output) {
	Card::save(output);
	output << endl;
}
CardFour::~CardFour()
{
}