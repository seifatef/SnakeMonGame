#include "CutCardAction.h"
#include"Input.h"
#include "Output.h"
#include "Grid.h"
#include "Card.h"

CutCardAction::CutCardAction(ApplicationManager* pApp): Action(pApp)
{

}

void CutCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Click on the source cell");
	CardPos = pIn->GetCellClicked();
	if (CardPos.HCell() == -1)
	{
		pGrid->PrintErrorMessage("Please click on a valid cell, Click to continue...");
	}
}

void CutCardAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (CardPos.HCell() == -1) return;
	pCard = pGrid->GetCardFromPosition(CardPos);
	if (pCard == NULL) {
		pGrid->PrintErrorMessage("No card at clicked position, Click to continue...");
		return;
	}

	pGrid->SetClipboard(pCard->CopyCard(CardPos));
	pGrid->RemoveObjectFromCell(CardPos);
	pGrid->PrintErrorMessage("Card Cut succesfully, Click to continue...");
}

CutCardAction::~CutCardAction()
{
}
