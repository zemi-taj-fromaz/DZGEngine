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
	L = 6,
	S = 7,
	Z = 8
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
		//type = TetrominoType::I;
		//Positions.push_back({ 0,5 });
		//Positions.push_back({ 1,5 });
		//Positions.push_back({ 2,5 });
		//Positions.push_back({ 3,5 });

		//type = TetrominoType::J;
		//Positions.push_back({ 0,5 });
		//Positions.push_back({ 1,5 });
		//Positions.push_back({ 2,5 });
		//Positions.push_back({ 2,4 });

		//type = TetrominoType::L;
		//Positions.push_back({ 0,5 });
		//Positions.push_back({ 1,5 });
		//Positions.push_back({ 2,5 });
		//Positions.push_back({ 2,6 });

		//type = TetrominoType::T;
		//Positions.push_back({ 1,4 });
		//Positions.push_back({ 1,5 });
		//Positions.push_back({ 1,6 });
		//Positions.push_back({ 2,5 });

		type = TetrominoType::S;
		Positions.push_back({ 1,5 });
		Positions.push_back({ 1,4 });
		Positions.push_back({ 2,4 });
		Positions.push_back({ 2,3 });

		//type = TetrominoType::Z;
		//Positions.push_back({ 1,4 });
		//Positions.push_back({ 1,5 });
		//Positions.push_back({ 2,5 });
		//Positions.push_back({ 2,6 });

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
	void RotateI(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RotateJ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RotateL(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RotateT(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RotateS(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RotateZ(std::vector<std::shared_ptr<Mesh>>& MeshVec);

	void LeftI(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void LeftJ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void LeftL(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void LeftT(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void LeftS(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void LeftZ(std::vector<std::shared_ptr<Mesh>>& MeshVec);

	void RightI(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightJ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightL(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightT(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightS(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightZ(std::vector<std::shared_ptr<Mesh>>& MeshVec);


	void DownI(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void DownJ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void DownL(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void DownT(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void DownS(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void DownZ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
};

