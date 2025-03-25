#include "CardNine.h"
#include <fstream>
CardNine::CardNine(const CellPosition& Cell_Pos): Card(Cell_Pos)
{
	cardNumber = 9;
}

void CardNine::ReadCardParameters(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput(); // returns an output pointer
	Input* pIn = pGrid->GetInput();    // returns an input pointer
	// we used an output pointer as the grid pointer has no accessibility on the cicked cell

	pOut->PrintMessage("CardNine: choose the move to cell! Click to continue...");
	StoppingCell = pIn->GetCellClicked();
	if (!StoppingCell.IsValidCell() || StoppingCell.GetCellNum() == this->GetPosition().GetCellNum())
	{
		pGrid->PrintErrorMessage("Invalid cell, Click to continue...");

	}
	pOut->ClearStatusBar(); // clear for the next operation

}

bool CardNine::UserInputValidation()
{
	if (!StoppingCell.IsValidCell())
		return false;
	return true;
}

bool CardNine::TakesParameters() const
{
	return true;
}

void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	if (StoppingCell.IsValidCell() || !(StoppingCell.GetCellNum() == this->GetPosition().GetCellNum()))
	{
		int newposition = StoppingCell.GetCellNum() - (pPlayer->GetCell()->GetCellPosition().GetCellNum()); //calculating what cells u gotta move 
		pPlayer->decrementTurnCount();
		pPlayer->Move(pGrid, newposition);

	}



}

Card* CardNine::CopyCard(CellPosition& pos)
{
	return new CardNine(pos);
}

bool CardNine::EditParameters(Grid* pGrid)
{
	CellPosition currPos = StoppingCell;
	ReadCardParameters(pGrid);
	if (!StoppingCell.IsValidCell() || StoppingCell.GetCellNum() == this->GetPosition().GetCellNum()) {
		StoppingCell = currPos;
		return false;
	}
	return true;
}

void CardNine::save(ofstream& output)
{
	Card::save(output);
	output << " " << StoppingCell.GetCellNumFromPosition(StoppingCell) << endl;
}

void CardNine::load(ifstream& input)
{
	int cellNum;
	input >> cellNum;
	this->StoppingCell = CellPosition::GetCellPositionFromNum(cellNum);
}

CardNine::~CardNine()
{
}
