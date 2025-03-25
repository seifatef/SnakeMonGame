#include "CardSeven.h"
#include <fstream>


CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; //sets the inherited cardNumber data member with the card number (7 here)
}


void CardSeven::ReadCardParameters(Grid* pGrid)
{

}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);

	pGrid->PrintErrorMessage("This card gives you another dice roll. Click to continue...");

	int player_num = pPlayer->GetPlayerNumber();

	for (int i = 0; i < 3; i++) pGrid->AdvanceCurrentPlayer();
	pPlayer->decrementTurnCount();
	pGrid->PrintErrorMessage("Player " + to_string(player_num) + " Got an extra dice roll, Click to continue...");
}

Card* CardSeven::CopyCard(CellPosition& pos)
{
	return new CardSeven(pos);
}

void CardSeven::save(ofstream& output)
{
	Card::save(output);
	output << endl;
}


CardSeven::~CardSeven()
{
}