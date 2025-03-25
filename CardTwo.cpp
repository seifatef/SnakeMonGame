#include "CardTwo.h"
#include <fstream>
CardTwo::CardTwo(const CellPosition& Cell_Pos): Card(Cell_Pos)
{
	cardNumber = 2;
	AddedValue = -1;
}
void CardTwo::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Enter the value to be incremented");
	AddedValue = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();
	if (AddedValue <= 0)
	{
		AddedValue = 0;
		pGrid->PrintErrorMessage("Invalid, Click to continue...");
	}
}

bool CardTwo::UserInputValidation()
{
	if (AddedValue >= 0) return true;
	return false;
}

bool CardTwo::TakesParameters() const
{
	return true;
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{

		Card::Apply(pGrid, pPlayer);
		int newVal = pPlayer->GetWallet() + AddedValue;
		pPlayer->SetWallet(newVal);
}

Card* CardTwo::CopyCard(CellPosition& pos)
{
	return new CardTwo(pos);
}

bool CardTwo::EditParameters(Grid* pGrid)
{
	int currVal = AddedValue;
	ReadCardParameters(pGrid);
	if (!AddedValue) {
		AddedValue = currVal;
		return false;
	}
	return true;
}

void CardTwo::save(ofstream& output) {
	Card::save(output);
	output << " " << AddedValue << endl;
}

void CardTwo::load(ifstream& input)
{
	int val;
	input >> val;
	this->AddedValue = val;
}

CardTwo::~CardTwo()
{
}
