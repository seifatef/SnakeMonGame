#pragma once
#include "Action.h"
class SaveGridAction : public Action
{
private:
	string fileName;
public:
	SaveGridAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SaveGridAction(); // A Virtual Destructor
};

