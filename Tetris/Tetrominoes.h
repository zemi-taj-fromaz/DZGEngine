#pragma once

#include <vector>

enum TetrominoaType
{
	UNDEFINED = 0,
	SQUARE = 1,
};

enum Input
{
	NOINPUT = 0,
	DOWN = 1,
};

class Tetrominoes
{
public:
	Tetrominoes()
	{
		type = TetrominoaType::SQUARE;
		Positions.push_back({ 0,5 });
		/* select random Type and select random spawn position(random collumn)*/
	}

	void processDown();
	void processUp();
	void processLeft();
	void processRight();
	
	TetrominoaType type;
	std::vector<std::pair<int, int> > Positions;
};

