#pragma once
#include "Action.h"
class DeleteGameObjectAction : public Action
{
	CellPosition cellPosition; // the cell you need to delete
public:

DeleteGameObjectAction(ApplicationManager* pApp);

virtual void ReadActionParameters();

virtual void Execute();

virtual ~DeleteGameObjectAction();
};

