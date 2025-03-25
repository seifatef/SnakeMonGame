#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager *pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

void AddLadderAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid *pGrid = pManager->GetGrid();
	Output *pOut = pGrid->GetOutput();
	Input *pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	if (startPos.VCell() == 0)
	{
		pGrid->PrintErrorMessage("Error: The starting cell cannot be in the final row! Click to continue ...");
		startPos = CellPosition(-1, -1);
		return;
	}
	else if (startPos.VCell() == 8 && startPos.HCell() == 0)
	{
		pGrid->PrintErrorMessage("Error: The starting cell cannot be in the first column of the first row! Click to continue ...");
		startPos = CellPosition(-1, -1);
		return;
	}
	else if (startPos.HCell() == -1) {
		pGrid->PrintErrorMessage("Error: Invalid Location for the starting cell! Click to continue ...");
		startPos = CellPosition(-1, -1);
		return;
	}
	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	if (endPos.HCell() == -1) {
		pGrid->PrintErrorMessage("Error: Invalid Location for the ending cell! Click to continue ...");
		startPos = CellPosition(-1, -1);
		return;
	}
	/// TODO: Make the needed validations on the read parameters



	if (startPos.HCell() != endPos.HCell())
	{
		pGrid->PrintErrorMessage("Error: The starting cell and the ending cell must be in the same column! Click to continue ...");
		startPos = CellPosition(-1, -1);
	}

	else if (startPos.VCell() < endPos.VCell())
	{

		pGrid->PrintErrorMessage("Error: The ending cell must be above the starting cell! Click to continue ...");
		startPos = CellPosition(-1, -1);
	}

	else if (startPos.HCell() == endPos.HCell() && startPos.VCell() == endPos.VCell())
	{
		pGrid->PrintErrorMessage("Error: The starting cell and the ending cell are identical! Click to continue ...");
		startPos = CellPosition(-1, -1);
	}

	// Clear messages
	pOut->ClearStatusBar();
}

// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Ladder *pLadder = new Ladder(startPos, endPos);

	Grid *pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Can't add Ladder here! Click to continue ...");
		return;
	}
	Output* pOut = pGrid->GetOutput();
	pLadder->Draw(pOut);
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
}

AddLadderAction::~AddLadderAction()
{
}