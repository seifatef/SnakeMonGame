#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
											   // from the passed (cellNum)
											   // (*this) = ... --> this will copy the returned (vCell and hCell)
											   //                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	/// TODO: Implement this function as described in the .h file (don't forget the validation)

	if (v >= 0 && v <= 8) 
	{
		vCell = v;
		return true;
	}

	return false; 
}

bool CellPosition::SetHCell(int h)
{
	/// TODO: Implement this function as described in the .h file (don't forget the validation)
	if (h >= 0 && h <= 10)
	{
		hCell = h;
		return true;
	} 
	return false;
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	/// TODO: Implement this function as described in the .h file
	if (vCell >= 0 && vCell <= 8 && hCell >= 0 && hCell <= 10)
		return true; // this line sould be changed with your implementation
	return false;
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition &cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	/// TODO: Implement this function as described in the .h file
	if (cellPosition.IsValidCell())
	{
		int cellNumber;
		cellNumber = (8 - cellPosition.VCell()) * NumHorizontalCells + (cellPosition.HCell() + 1);
		
		return cellNumber;
	}
	return 0; //invalid Position
	// this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file
	if (cellNum < 1 || cellNum > 99)
		return position;
	int unitsNum = cellNum % 10;
	int tensNum = cellNum / 10;
	int hCell = -1;
	if (unitsNum > tensNum)
		hCell = unitsNum - tensNum - 1;
	else
		hCell = unitsNum + 10 - tensNum;
	int vCell = 8 - ((cellNum - 1) / 11);

	position.SetHCell(hCell);
	position.SetVCell(vCell);

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it

	return position;
}

void CellPosition::AddCellNum(int addedNum)
{

	/// TODO: Implement this function as described in the .h file
	int CellNum = addedNum + GetCellNumFromPosition( *(this) );
	CellPosition NewCell(CellNum);
	
	// Note: this function updates the data members (vCell and hCell) of the calling object
	*this = NewCell;
}