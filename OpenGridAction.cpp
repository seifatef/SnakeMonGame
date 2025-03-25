#include "OpenGridAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Snake.h"
#include "Ladder.h"
#include "Card.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardThree.h"
#include "CardFour.h"
#include "CardFive.h"
#include "CardSix.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include <fstream>

OpenGridAction::OpenGridAction(ApplicationManager* pApp) : Action(pApp) { }

OpenGridAction::~OpenGridAction() {};

void OpenGridAction::ReadActionParameters() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Please enter the file name, then press ENTER");
	fileName = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
}

void OpenGridAction::Execute() {
	ReadActionParameters();
	if (fileName.length() == 0) {
		Grid* pGrid = pManager->GetGrid();
		pGrid->PrintErrorMessage("File name can't be empty.");
		return;
	}
	ifstream InputFile(fileName + ".txt");
	Grid* pGrid = pManager->GetGrid();
	if (InputFile.fail()) {
		pGrid->PrintErrorMessage("File doesn't exist or is corrupted.");
		return;
	}
	pGrid->Clear();
	int numberOfSnakes;
	InputFile >> numberOfSnakes;
	for (int i = 0; i < numberOfSnakes; i++) {
		int startCell, endCell;
		InputFile >> startCell >> endCell;
		Snake* S = new Snake(CellPosition::GetCellPositionFromNum(startCell), CellPosition::GetCellPositionFromNum(endCell));
		pGrid->AddObjectToCell(S);
	}
	int numberOfLadders;
	InputFile >> numberOfLadders;
	for (int i = 0; i < numberOfLadders; i++) {
		int startCell, endCell;
		InputFile >> startCell >> endCell;
		Ladder* L = new Ladder(CellPosition::GetCellPositionFromNum(startCell), CellPosition::GetCellPositionFromNum(endCell));
		pGrid->AddObjectToCell(L);
	}
	int numberOfCards;
	InputFile >> numberOfCards;
	Card* c;
	for (int i = 0; i < numberOfCards; i++) {
		int cardNum, cellNum;
		InputFile >> cardNum;
		InputFile >> cellNum;
		switch (cardNum) {
		case 1:
			c = new CardOne(CellPosition::GetCellPositionFromNum(cellNum));
			c->load(InputFile);
			pGrid->AddObjectToCell(c);
			break;
		case 2:
			c = new CardTwo(CellPosition::GetCellPositionFromNum(cellNum));
			c->load(InputFile);
			pGrid->AddObjectToCell(c);
			break;
		case 3:
			c = new CardThree(CellPosition::GetCellPositionFromNum(cellNum));
			pGrid->AddObjectToCell(c);
			break;
		case 4:
			c = new CardFour(CellPosition::GetCellPositionFromNum(cellNum));
			pGrid->AddObjectToCell(c);
			break;
		case 5:
			c = new CardFive(CellPosition::GetCellPositionFromNum(cellNum));
			pGrid->AddObjectToCell(c);
			break;
		case 6:
			c = new CardSix(CellPosition::GetCellPositionFromNum(cellNum));
			pGrid->AddObjectToCell(c);
			break;
		case 7:
			c = new CardSeven(CellPosition::GetCellPositionFromNum(cellNum));
			pGrid->AddObjectToCell(c);
			break;
		case 8:
			c = new CardEight(CellPosition::GetCellPositionFromNum(cellNum));
			pGrid->AddObjectToCell(c);
			break;
		case 9:
			c = new CardNine(CellPosition::GetCellPositionFromNum(cellNum));
			c->load(InputFile);
			pGrid->AddObjectToCell(c);
			break;
		case 10:
			c = new CardTen(CellPosition::GetCellPositionFromNum(cellNum));
			c->load(InputFile);
			pGrid->AddObjectToCell(c);
			CardTen::setLoaded(true);
			break;
		case 11:
			c = new CardEleven(CellPosition::GetCellPositionFromNum(cellNum));
			c->load(InputFile);
			pGrid->AddObjectToCell(c);
			CardEleven::setLoaded(true);
			break;
		case 12:
			c = new CardTwelve(CellPosition::GetCellPositionFromNum(cellNum));
			c->load(InputFile);
			pGrid->AddObjectToCell(c);
			CardTwelve::setLoaded(true);
			break;
		case 13:
			c = new CardThirteen(CellPosition::GetCellPositionFromNum(cellNum));
			c->load(InputFile);
			pGrid->AddObjectToCell(c);
			CardThirteen::setLoaded(true);
			break;
		default:
			pGrid->PrintErrorMessage("An entry in the file is corrupted..");
		}
	}
	CardTen::setLoaded(false);
	CardEleven::setLoaded(false);
	CardTwelve::setLoaded(false);
	CardThirteen::setLoaded(false);
}