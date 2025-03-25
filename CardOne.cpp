#include "CardOne.h"
#include <fstream>
#include "Player.h"

CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
	walletAmount = -1;
}

CardOne::~CardOne(void)
{
}

void CardOne::ReadCardParameters(Grid * pGrid)
{
	
	
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."

	
		pOut->PrintMessage("Input value to be decreased from passing player's wallets...");
		walletAmount = pIn->GetInteger(pOut);
		if (walletAmount <= 0) {
			pGrid->PrintErrorMessage("you entered invalid value, Click to continue...");
		}
	// [ Note ]:
	// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
	// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
	// to be able to perform his Apply() action

	// 3- Clear the status bar
	pOut->ClearStatusBar();
}
bool CardOne::UserInputValidation()
{
	if (walletAmount >= 0) return true;
	return false;
}

bool CardOne::TakesParameters() const
{
	return true;
}

Card* CardOne::CopyCard(CellPosition& pos)
{
	return new CardOne(pos);
}

bool CardOne::EditParameters(Grid* pGrid)
{
	int currWallet = this->walletAmount;
	ReadCardParameters(pGrid);
	if (walletAmount <= 0) {
		walletAmount = currWallet;
		return false;
	}
	return true;
}

void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{
		
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	

	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	// 2- Decrement the wallet of pPlayer by the walletAmount data member of CardOne
	int currentWallet = pPlayer->GetWallet();
	pPlayer->SetWallet(currentWallet - walletAmount);
}

void CardOne::save(ofstream& output) {
	Card::save(output);
	output << " " << walletAmount << endl;
}

void CardOne::load(ifstream& input)
{
	int wallet;
	input >> wallet;
	this->walletAmount = wallet;
}
