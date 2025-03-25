#include "PasteCardAction.h"
#include"Input.h"
#include "Output.h"
#include "Grid.h"
#include "Card.h"

PasteCardAction::PasteCardAction(ApplicationManager* pApp):Action(pApp)
{
	
}

void PasteCardAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("Click on the destination cell");
	CardPosition = pIn->GetCellClicked();
	if (CardPosition.HCell() == -1)
	{
		pGrid->PrintErrorMessage("Please click on a valid cell, Click to continue...");
	}
}

void PasteCardAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (CardPosition.HCell() == -1) return;
	if (!pGrid->GetClipboard()) {
		pGrid->PrintErrorMessage("No card saved on clipboard, Click to continue...");
		return;
	}
	pCard = pGrid->GetClipboard()->CopyCard(CardPosition);
	pGrid->AddObjectToCell(pCard);
	delete pGrid->GetClipboard();
	pCard->Draw(pGrid->GetOutput());
	pGrid->SetClipboard(NULL);
	pGrid->PrintErrorMessage("Card Pasted succesfully, Click to continue...");
}

PasteCardAction::~PasteCardAction()
{

}
