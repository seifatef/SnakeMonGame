#include "Grid.h"
#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include "Player.h"
#include <fstream>

Grid::Grid(Input *pIn, Output *pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells - 1][0], i); // first cell
		PlayerList[i]->Draw(pOut);										  // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}

// ========= Adding or Removing GameObjects to Cells =========

bool Grid::AddObjectToCell(GameObject *pNewObject) // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject *pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false
		if (!dynamic_cast<Card *>(pNewObject))
			if (Grid::IsOverlapping(pNewObject))
				return false;
		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

bool Grid::IsOverlapping(GameObject *newObj) const
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasLadder() || CellList[i][j]->HasSnake())
			{ // loops on all the cells and checks the overlapping member function of cells
				if (newObj->IsOverlapping(CellList[i][j]->GetGameObject()))
				{ // with snake or ladder
					return true;
				}
			}
		}
	}
	return false;
}
bool Grid::RemoveObjectFromCell(const CellPosition &pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		if (CellList[pos.VCell()][pos.HCell()]->GetGameObject() != NULL)
		{
			// Note: you can deallocate the object here before setting the pointer to null if it is needed
			delete CellList[pos.VCell()][pos.HCell()]->GetGameObject(); // Deallocate the memory reserved for the game object (Ladder, snake, card)
			CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
			return true;
		}
	}
	return false;
}

void Grid::Clear()
{
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
			RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
}

Card *Grid::GetCardFromPosition(const CellPosition &pos)
{
	GameObject *pObj = CellList[pos.VCell()][pos.HCell()]->GetGameObject(); // Assuming a 2D CellList
	return dynamic_cast<Card *>(pObj);										// Ensure the object is a Card
}

void Grid::UpdatePlayerCell(Player *player, const CellPosition &newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell *newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
	if (newCell->GetGameObject() != NULL)
		newCell->GetGameObject()->Apply(this, player);
}

void Grid::ResetPlayers()
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		CellPosition c(1);
		UpdatePlayerCell(PlayerList[i], c);
		PlayerList[i]->ResetPlayer();
	}
	currPlayerNumber = 0;
}

// ========= Setters and Getters Functions =========

Input *Grid::GetInput() const
{
	return pIn;
}

Output *Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card *pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card *Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

int Grid::GetNumberOfSnakes() const
{
	int SnakesCount = 0;
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
			if (CellList[i][j]->HasSnake())
				SnakesCount++;
	return SnakesCount;
}

int Grid::GetNumberOfLadders() const
{
	int LaddersCount = 0;
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
			if (CellList[i][j]->HasLadder())
				LaddersCount++;
	return LaddersCount;
}

int Grid::GetNumberOfCards() const
{
	int CardsCount = 0;
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
			if (CellList[i][j]->HasCard())
				CardsCount++;
	return CardsCount;
}

void Grid::SaveSnakes(ofstream &outputfile)
{
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
			if (CellList[i][j]->HasSnake())
			{
				Snake *s = dynamic_cast<Snake *>(CellList[i][j]->GetGameObject());
				outputfile << s->GetPosition().GetCellNumFromPosition(s->GetPosition()) << " " << s->GetEndPosition().GetCellNumFromPosition(s->GetEndPosition()) << endl;
			}
}

void Grid::SaveLadders(ofstream &outputfile)
{
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
			if (CellList[i][j]->HasLadder())
			{
				Ladder *L = dynamic_cast<Ladder *>(CellList[i][j]->GetGameObject());
				outputfile << L->GetPosition().GetCellNumFromPosition(L->GetPosition()) << " " << L->GetEndPosition().GetCellNumFromPosition(L->GetEndPosition()) << endl;
			}
}

void Grid::SaveCards(ofstream &outputfile)
{
	bool ten_saved = false;
	bool eleven_saved = false;
	bool twelve_saved = false;
	bool thirteen_saved = false;
	for (int i = 0; i < NumVerticalCells; i++)
		for (int j = 0; j < NumHorizontalCells; j++)
			if (CellList[i][j]->HasCard())
			{
				Card *C = dynamic_cast<Card *>(CellList[i][j]->GetGameObject());
				C->save(outputfile);
				if (dynamic_cast<CardTen*>(C)) {
					CardTen::setSaved(true);
				}
				if (dynamic_cast<CardEleven*>(C)) {
					CardEleven::setSaved(true);
				}
				if (dynamic_cast<CardTwelve*>(C)) {
					CardTwelve::setSaved(true);
				}
				if (dynamic_cast<CardThirteen*>(C)) {
					CardThirteen::setSaved(true);
				}
			}
	CardTen::setSaved(false);
	CardEleven::setSaved(false);
	CardTwelve::setSaved(false);
	CardThirteen::setSaved(false);
}
// ========= Other Getters =========

Player *Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder *Grid::GetNextLadder(const CellPosition &position)
{

	int startH = position.HCell();				// represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			/// TODO: Check if CellList[i][j] has a ladder, if yes return it
			if (CellList[i][j]->HasLadder() != NULL)
				return dynamic_cast<Ladder *>(CellList[i][j]->GetGameObject()); // Cast the GameObject pointer to ladder pointer to match return type
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Snake *Grid::GetNextSnake(const CellPosition &position)
{

	int startH = position.HCell();				// represents the start hCell in the current row to search for the snake in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			if (CellList[i][j]->HasSnake() != NULL)
				return dynamic_cast<Snake *>(CellList[i][j]->GetGameObject()); // Cast the GameObject pointer to snake pointer to match return type
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

// ========= User Interface Functions =========

void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells - 1; i >= 0; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount - 1)					  // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::launchAttack(int attacker, int pIdx, int attack)
{
	switch (attack) {
	case 1:
		PlayerList[pIdx]->PreventPlaying();
		PrintErrorMessage("Player " + to_string(attacker) + " attacked player " + to_string(pIdx) + " with the Ice attack!");
		break;
	case 2:
		PlayerList[pIdx]->addFire(3);
		PrintErrorMessage("Player " + to_string(attacker) + " attacked player " + to_string(pIdx) + " with the Fire attack!");
		break;
	case 3:
		PlayerList[pIdx]->addPoison(5);
		PrintErrorMessage("Player " + to_string(attacker) + " attacked player " + to_string(pIdx) + " with the Poison attack!");
		break;
	case 4:
		for (int i = 0; i < 4; i++) {
			if (i != attacker) {
				PlayerList[i]->SetWallet(PlayerList[i]->GetWallet() - 20);
			}
		}
		PrintErrorMessage("Player " + to_string(attacker) + " launched the Lightining attack!");
		break;
	}
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject())
				delete CellList[i][j]->GetGameObject(); // Deallocate the game object
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}