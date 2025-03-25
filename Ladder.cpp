#include "Ladder.h"
#include "Snake.h"
#include "Grid.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// == Here are some guideline steps (numbered below) to implement this function ==
	
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a ladder. Click to continue ...");
	pIn->GetCellClicked();
	pOut->ClearStatusBar();

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	if (endCellPos.GetCellNumFromPosition(endCellPos) == 99) {
		pGrid->SetEndGame(true);
	}

}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

bool Ladder::IsOverlapping(GameObject* newObj) const
{
	if (this->GetPosition().HCell() != newObj->GetPosition().HCell()) return false;
	Ladder* L1 = dynamic_cast<Ladder*>(newObj);
	if (L1)
	{
		if ( (this->GetPosition().VCell() <= L1->GetPosition().VCell() && this->GetPosition().VCell() >= L1->GetEndPosition().VCell() ) || (this->GetEndPosition().VCell() <= L1->GetPosition().VCell() && this->GetEndPosition().VCell() >= L1->GetEndPosition().VCell()))
		{
			return true;
		}
		else if ((L1->GetPosition().VCell() <= this->GetPosition().VCell() && L1->GetPosition().VCell() >= this->GetEndPosition().VCell()) || (L1->GetEndPosition().VCell() <= this->GetPosition().VCell() && L1->GetEndPosition().VCell() >= this->GetEndPosition().VCell())) {
			return true;
		}
		return false;
	}
	else
	{
		Snake* S1 = dynamic_cast<Snake*>(newObj);
		if ( this->GetPosition().VCell() == S1->GetPosition().VCell() || this->GetPosition().VCell() == S1->GetEndPosition().VCell() || this->GetEndPosition().VCell() == S1->GetPosition().VCell() )
		{
			return true;
		}
		return false;
	}
}



Ladder::~Ladder()
{
}
