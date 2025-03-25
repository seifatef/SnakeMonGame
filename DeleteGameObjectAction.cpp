#include "DeleteGameObjectAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{

}


void DeleteGameObjectAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Click on the cell that you want to delete its game object.");
	cellPosition = pIn->GetCellClicked();
	pOut->ClearStatusBar();
}
void DeleteGameObjectAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	bool IsObjectDeleted = pGrid->RemoveObjectFromCell(cellPosition);
	if (!IsObjectDeleted)
		pGrid->PrintErrorMessage("Error: The cell you clicked is already empty ! Click to continue ...");
}


DeleteGameObjectAction::~DeleteGameObjectAction()
{
}