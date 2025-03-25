#include "MonopolyCards.h"

MonopolyCards::MonopolyCards(const CellPosition& pos) : Card(pos) {};

int MonopolyCards::ReadCardPrice(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	int price = -1;
	pOut->PrintMessage("Input price of the station...");
	price = pIn->GetInteger(pOut);
	if (price <= 0) {
		price = 0;
		pGrid->PrintErrorMessage("Invalid price value, Click to continue...");
	}
	return price;
}

int MonopolyCards::ReadCardFees(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	int fees = -1;
	pOut->PrintMessage("Input fees of the station...");
	fees = pIn->GetInteger(pOut);
	if (fees <= 0) {
		fees = 0;
		pGrid->PrintErrorMessage("Invalid fees value, Click to continue...");
	}
	return fees;
}


bool MonopolyCards::TakesParameters() const
{
	return true;
}
