#pragma once
#include "GameObject.h"
class Snake : public GameObject 
{
private :
	CellPosition endCellPos; //represents the end of the cell position 


public :
	Snake(const CellPosition& startCellPos1, const CellPosition& endCellPos1);
	virtual void Draw(Output* pOut) const;
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	CellPosition GetEndPosition() const;


	bool Snake::IsOverlapping(GameObject* newObj) const;


	virtual ~Snake();

};

