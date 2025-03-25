#pragma once
#include "Action.h"
class EditCardAction : public Action
{

    CellPosition cardPos; // Position of the card to edit
    Card* pCard;          // Pointer to the card being edited

public:
    EditCardAction(ApplicationManager* pApp); // Constructor

    // Reads parameters required for action to execute
    virtual void ReadActionParameters();

    // Executes the action (edit the card at the selected cell)
    virtual void Execute();

    virtual ~EditCardAction();                // Destructor
};