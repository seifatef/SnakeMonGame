#pragma once
#include "Action.h"
class InputDiceValAction : public Action
{
	int DiceValue;
public:
	InputDiceValAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~InputDiceValAction();
};