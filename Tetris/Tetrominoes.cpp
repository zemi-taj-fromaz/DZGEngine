#include "Tetrominoes.h"

void Tetrominoes::processDown()
{
	/*
		TODO - this check needs to be modified to see if movement is possible
	*/
	for (auto& pair : Positions)
	{
		if (pair.first == 19) return;
	}

	for (auto& pair : Positions)
	{
		pair.first += 1;
	}
}
void Tetrominoes::processUp(){}
void Tetrominoes::processLeft()
{
	for (auto& pair : Positions)
	{
		if (pair.second == 0) return;
	}

	for (auto& pair : Positions)
	{
		pair.second -= 1;
	}
}
void Tetrominoes::processRight()
{

	for (auto& pair : Positions)
	{
		if (pair.second == 9) return;
	}

	for (auto& pair : Positions)
	{
		pair.second += 1;
	}
	
}