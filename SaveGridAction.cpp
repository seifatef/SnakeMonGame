#include "SaveGridAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"
#include <fstream>
SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp) { };
SaveGridAction::~SaveGridAction() { };

void SaveGridAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Please enter the file name, then press ENTER");
	fileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void SaveGridAction::Execute() {
	ReadActionParameters();
	if (fileName.length() == 0) {
		Grid* pGrid = pManager->GetGrid();
		pGrid->PrintErrorMessage("File name can't be empty.");
		return;
	}
	ofstream outputFile(fileName + ".txt");
	if (outputFile.fail()) {
		Grid* pGrid = pManager->GetGrid();
		pGrid->PrintErrorMessage("Couldn't save the grid to file " + fileName + ".");
		return;
	}
	Grid* pGrid = pManager->GetGrid();
	outputFile <<  pGrid->GetNumberOfSnakes() << endl;
	pGrid->SaveSnakes(outputFile);
	outputFile << pGrid->GetNumberOfLadders() << endl;
	pGrid->SaveLadders(outputFile);
	int numberOfCards = pGrid->GetNumberOfCards();
	outputFile << numberOfCards << endl;
	pGrid->SaveCards(outputFile);

	outputFile.close();
}