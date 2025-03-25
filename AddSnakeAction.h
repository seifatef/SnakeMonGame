#pragma once
#include "Action.h"
class AddSnakeAction : public Action
{

	CellPosition Start_Pos;
	CellPosition End_Pos;

public :
	AddSnakeAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~AddSnakeAction();
};

