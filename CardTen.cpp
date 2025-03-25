#include "CardTen.h"
#include <fstream>
CardTen::CardTen(const CellPosition& pos) : MonopolyCards(pos) { cardNumber = 10; }
CardTen::~CardTen() {
	CardTen::count--;
	if (!CardTen::count) {
		CardTen::fees = 0;
		CardTen::price = 0;
	}
}

int CardTen::fees = 0;
int CardTen::price = 0;
Player* CardTen::pPlayer = NULL;
bool CardTen::saved = false;
bool CardTen::loaded = false;
int CardTen::count = 0;

void CardTen::ReadCardParameters(Grid* pGrid) {
	if (price != 0 && fees != 0) return;
	price = ReadCardPrice(pGrid); // Call the functions of the parent class (MonopolyCards)
	if (!price) return;
	fees = ReadCardFees(pGrid);
	if (!fees) { price = 0; return; }
}

bool CardTen::UserInputValidation()
{
	if (price <= 0 || fees <= 0)
		return false;
	CardTen::count++;
	return true;
}

void CardTen::Apply(Grid* pGrid, Player* pPlayer) {
	Card::Apply(pGrid, pPlayer);  // Output the default message
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	if (this->pPlayer == NULL) { // if the station wasn't bought by another player
		pOut->PrintMessage("Would you like to buy this station for " + to_string(this->price) + "? [y\\n]");
		string answer = pIn->GetSrting(pOut);
		while (answer != "n" && answer != "y") answer = pIn->GetSrting(pOut); // Loop until the user gives appropriate answer
		if (answer == "y") {
			if (pPlayer->GetWallet() >= this->price) {
				int currentWallet = pPlayer->GetWallet();
				pPlayer->SetWallet(currentWallet - this->price);
				this->pPlayer = pPlayer;
				pGrid->PrintErrorMessage("You succefully bought station number " + to_string(this->cardNumber));
				return;
			}
			else {
				pGrid->PrintErrorMessage("You can't afford the current station.");
				return;
			}
		}
	}
	else {
		pGrid->PrintErrorMessage("You landed on the station owned by player " + to_string(this->pPlayer->GetPlayerNumber()) + ", A fee of " + to_string(fees) + " is to be paid. Click to Continue...");
		this->pPlayer->SetWallet(this->pPlayer->GetWallet() + fees);
		pPlayer->SetWallet(pPlayer->GetWallet() - fees);
		return;
	}
}

Card* CardTen::CopyCard(CellPosition& pos)
{
	return new CardTen(pos);
}

bool CardTen::EditParameters(Grid* pGrid)
{
	int f = this->fees;
	int p = this->price;
	price = ReadCardPrice(pGrid);
	fees = ReadCardFees(pGrid);
	if (price == -1 || fees == -1) {
		price = p;
		fees = f;
		return false;
	}
	return true;
}

void CardTen::save(ofstream& output) {
	Card::save(output);
	if (!this->saved)
		output << " " << price << " " << fees << endl;
	else output << endl;
}

void CardTen::load(ifstream& input)
{
	if (!CardTen::loaded) {
		int p, f;
		input >> p >> f;
		this->price = p;
		this->fees = f;
	}
}

void CardTen::resetOwnerShip()
{
	pPlayer = NULL;
}

void CardTen::setSaved(bool s)
{
	CardTen::saved = true;
}

void CardTen::setLoaded(bool l)
{
	CardTen::loaded = l;
}
