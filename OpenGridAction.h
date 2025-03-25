#pragma once
#include "Action.h"
class OpenGridAction : public Action
{
private:
	string fileName;
public:
	OpenGridAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~OpenGridAction(); // A Virtual Destructor
};

