#include "Player.h"

#include "GameObject.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	this->prevented = false;
	// Make all the needed initialization or validations
	this->justRolledDiceNum = -1;
	this->attacksDone = NOATTACK;
	this->fire = 0;
	this->poison = 0;
	this->attacksDone = 0;
}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if (wallet < 0) this->wallet = 0;
	this->wallet = wallet;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::decrementTurnCount()
{
	if (this->turnCount == 0) {
		this->turnCount = 2;
		return;
	}
	this->turnCount--;
}

int Player::GetPlayerNumber() const
{
	return this->playerNum;
}

int Player::GetJustRolledDiceNumber() const {
	return this->justRolledDiceNum;
}

void Player::addFire(int f)
{
	this->fire += f;
}

void Player::addPoison(int p)
{
	this->poison += p;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];


	///TODO: use the appropriate output function to draw the player with "playerColor"
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);
}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	
	
	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);
}

void Player::PreventPlaying()
{
	prevented = true;
}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{
	if (fire) {
		this->SetWallet(this->GetWallet() - 20);
		fire--;
	}
	if (poison) {
		diceNumber--;
		poison--;
	}
	if (prevented) {
		prevented = false;
		turnCount++;
		if (turnCount == 3) turnCount = 0;
		justRolledDiceNum = 0;
		pGrid->PrintErrorMessage("You are denied from playing this turn. Click to continue...");
		return;
	}
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	this->justRolledDiceNum = diceNumber;
	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	this->turnCount++;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (this->turnCount == 3) {
		turnCount = 0;
		if (attacksDone < 2) {
			Output* pOut = pGrid->GetOutput();
			Input* pIn = pGrid->GetInput();
			string prompt;
			do {
				pOut->PrintMessage("Do you wish to launch a special attack instead of recharging? y/n");
				prompt = pIn->GetSrting(pOut);
			} while (prompt != "y" && prompt != "n");
			if (prompt == "n") {
				pOut->PrintMessage("It's Time to recharge the wallet for Player " + to_string(GetPlayerNumber()) + " . Click to continue...");
				this->wallet += 10 * diceNumber;
				pGrid->PrintErrorMessage("The Money of Player: " + to_string(playerNum) + " has been Increased By: " + to_string(diceNumber * 10));
				return;
			}
			else {
				int attack;
				do {
					pOut->PrintMessage("Choose an attack [1] Ice [2] Fire [3] Poison [4] Lightining. You can't do the same attack twice! Click to Continue...");
					attack = pIn->GetInteger(pOut);
				} while (attack < 1 || attack > 4 || doneAttack == attack);
				int player;
				switch (attack) {
				case ICE:
					do {
						pOut->PrintMessage("Choose a player to attack with Ice attack...");
						player = pIn->GetInteger(pOut);
					} while (player < 0 || player > 3 || player == this->GetPlayerNumber());
					doneAttack = ICE;
					break;
				case FIRE:
					do {
						pOut->PrintMessage("Choose a player to attack with Fire attack...");
						player = pIn->GetInteger(pOut);
					} while (player < 0 || player > 3 || player == this->GetPlayerNumber());
					doneAttack = FIRE;
					break;
				case POISON:
					do {
						pOut->PrintMessage("Choose a player to attack with Poison attack...");
						player = pIn->GetInteger(pOut);
					} while (player < 0 || player > 3 || player == this->GetPlayerNumber());
					doneAttack = POISON;
					break;
				case LIGHTING:
					player = -1;
					doneAttack = LIGHTING;
					break;
				}
				pGrid->launchAttack(this->GetPlayerNumber(), player, attack);
				attacksDone++;
				return;
			}
		}
		else {
			pGrid->PrintErrorMessage("It's Time to recharge the wallet for Player " + to_string(GetPlayerNumber()) + " . Click to continue...");
			this->wallet += 10 * diceNumber;
			pGrid->PrintErrorMessage("The Money of Player: " + to_string(playerNum) + " has been Increased By: " + to_string(diceNumber * 10));
			return;
		}
	}
	// 3- Set the justRolledDiceNum with the passed diceNumber
	this->justRolledDiceNum = diceNumber;
	if (this->wallet == 0) return;
	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	CellPosition pos = pCell->GetCellPosition();
	int newCellNum = pos.GetCellNumFromPosition(pos) + diceNumber;
	if (newCellNum > 99) newCellNum = 99;
	CellPosition newPos = pos.GetCellPositionFromNum(newCellNum);
	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(this, newPos);

	// 6- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
	if (newCellNum == 99) {
		pGrid->SetEndGame(true);
		pGrid->PrintErrorMessage("The Game Has finished! Player : " + to_string(GetPlayerNumber()) + " Won!");
	}
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

void Player::ResetPlayer()
{
	wallet = 100;
	turnCount = 0;
}
