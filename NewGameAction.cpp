#include "NewGameAction.h"
#include "Grid.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp) {

}

void NewGameAction::ReadActionParameters()
{
}

void NewGameAction::Execute() {
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->ClearStatusBar();
	pGrid->ResetPlayers();
	CardTen::resetOwnerShip();
	CardEleven::resetOwnerShip();
	CardTwelve::resetOwnerShip();
	CardThirteen::resetOwnerShip();
	pGrid->SetEndGame(false);
}