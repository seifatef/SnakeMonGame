#pragma once
#include "MonopolyCards.h"
class CardTwelve : public MonopolyCards
{
private:
	static int price;
	static int fees;
	static Player* pPlayer;
	static bool saved;
	static bool loaded;
	static int count;
public:
	CardTwelve(const CellPosition& pos);
	void ReadCardParameters(Grid* pGrid);
	virtual bool UserInputValidation();
	void Apply(Grid* pGrid, Player* pPlayer);
	virtual Card* CopyCard(CellPosition& pos);
	virtual bool EditParameters(Grid* pGrid);
	virtual void save(ofstream& output);
	virtual void load(ifstream& input);
	static void resetOwnerShip();
	static void setSaved(bool s);
	static void setLoaded(bool l);
	~CardTwelve();
};

