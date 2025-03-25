#include "Card.h"
#include "fstream"


Card::Card(const CellPosition& pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

void Card::SetCardNumber(int cnum)
{
	if (cardNumber >= 1 || cardNumber <= 13)
		cardNumber = cnum; // needs validation
}

int Card::GetCardNumber()
{
	return cardNumber;
}

Card* Card::CopyCard(CellPosition& pos)
{
	
	return nullptr;
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position, cardNumber);

}

void Card::ReadCardParameters(Grid* pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

bool Card::UserInputValidation()
{
	return true;
}

bool Card::TakesParameters() const
{
	// Default implementation: Cards that don't take parameters return false
	return false;
}

bool Card::EditParameters(Grid* pGrid)
{
	// Default implementation: Cards that don't take parameters do nothing
	pGrid->PrintErrorMessage("This card does not support editing parameters, Click to continue...");
	return false;
}


void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

void Card::save(ofstream& output) {
	output << this->GetCardNumber() << " " << this->GetPosition().GetCellNumFromPosition(this->GetPosition());
}

void Card::load(ifstream& input)
{
}

Card::~Card()
{
}