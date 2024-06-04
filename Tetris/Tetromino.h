#pragma once

#include <vector>
#include <memory>
#include "Mesh.h"

enum TetrominoType
{
	UNDEFINED = 0,
	SQUARE = 1,
	I = 2,
	O = 3,
	T = 4,
	J = 5,
	L = 5,
	S = 6,
	Z = 7
};

enum Input
{
	NOINPUT = 0,
	DOWN = 1,
};

class Tetromino
{
public:
	Tetromino()
	{
		type = TetrominoType::I;
		Positions.push_back({ 0,5 });
		Positions.push_back({ 1,5 });
		Positions.push_back({ 2,5 });
		Positions.push_back({ 3,5 });
		rotationPos = 1;
		/* select random Type and select random spawn position(random collumn)*/
	}

	void processDown(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void processUp(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void processLeft(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void processRight(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	
	TetrominoType type;
	int rotationPos;
	std::vector<std::pair<int, int> > Positions;

private:
	void TransitionIfPossible(std::vector<std::shared_ptr<Mesh>>& MeshVec);
};

