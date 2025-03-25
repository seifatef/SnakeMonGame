#include "ToPlayModeAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"

ToPlayModeAction::ToPlayModeAction(ApplicationManager* pApp):Action(pApp)
{

}

void ToPlayModeAction::ReadActionParameters()
{

}

void ToPlayModeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->CreatePlayModeToolBar();
	CardTen::resetOwnerShip();
	CardEleven::resetOwnerShip();
	CardTwelve::resetOwnerShip();
	CardThirteen::resetOwnerShip();
	pGrid->SetEndGame(false);
}

ToPlayModeAction::~ToPlayModeAction()
{
}