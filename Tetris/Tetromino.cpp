#include "Tetromino.h"

#include "Field.h"

#include <random>

bool Tetromino::processDown(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (type == TetrominoType::I)	   return DownI(MeshVec);
	else if (type == TetrominoType::J) return DownJ(MeshVec);
	else if (type == TetrominoType::L) return DownL(MeshVec);
	else if (type == TetrominoType::T) return DownT(MeshVec);
	else if (type == TetrominoType::S) return DownS(MeshVec);
	else if (type == TetrominoType::Z) return DownZ(MeshVec);
	else if (type == TetrominoType::O) return DownO(MeshVec);
	return false;
}
void Tetromino::processUp(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (type == TetrominoType::I) RotateI(MeshVec);
	else if (type == TetrominoType::J) RotateJ(MeshVec);
	else if (type == TetrominoType::L) RotateL(MeshVec);
	else if (type == TetrominoType::T) RotateT(MeshVec);
	else if (type == TetrominoType::S) RotateS(MeshVec);
	else if (type == TetrominoType::Z) RotateZ(MeshVec);
}
void Tetromino::processLeft(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (type == TetrominoType::I) LeftI(MeshVec);
	else if (type == TetrominoType::J) LeftJ(MeshVec);
	else if (type == TetrominoType::L) LeftL(MeshVec);
	else if (type == TetrominoType::T) LeftT(MeshVec);
	else if (type == TetrominoType::S) LeftS(MeshVec);
	else if (type == TetrominoType::Z) LeftZ(MeshVec);
	else if (type == TetrominoType::O) LeftO(MeshVec);
}
void Tetromino::processRight(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (type == TetrominoType::I) RightI(MeshVec);
	else if (type == TetrominoType::J) RightJ(MeshVec);
	else if (type == TetrominoType::L) RightL(MeshVec);
	else if (type == TetrominoType::T) RightT(MeshVec);
	else if (type == TetrominoType::S) RightS(MeshVec);
	else if (type == TetrominoType::Z) RightZ(MeshVec);
	else if (type == TetrominoType::O) RightO(MeshVec);
}

bool Tetromino::IsAttached(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	for (auto& pos : Positions)
	{
		if (pos.first == 19) return true;
		std::pair<int, int > target = { pos.first + 1, pos.second };
		if (std::find(Positions.begin(), Positions.end(), target) == Positions.end())
		{
			if (dynamic_cast<Field*>(MeshVec[target.first * 10 + target.second].get())->IsTaken()) return true;
		}
	}
	return false;
}

TetrominoType Tetromino::GenerateType()
{
	static std::mt19937 generator(std::time(nullptr)); // Seed the generator
	static std::uniform_int_distribution<int> distribution(2, 8); // Define the range
	return static_cast<TetrominoType>(distribution(generator));
}

glm::vec4 Tetromino::GenerateColor()
{
	static std::mt19937 generator(std::time(nullptr)); // Seed the generator
	static std::uniform_real_distribution<float> distribution(0.0f, 1.0f); // Define the range
	return glm::vec4(distribution(generator), distribution(generator), distribution(generator), 1.0f);
}

void Tetromino::RotateI(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second < 2) return;
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 2;
		int newPos0y = currPos0y - 2;

		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y - 1;

		int newPos2x = currPos2x;
		int newPos2y = currPos2y;

		int newPos3x = currPos3x - 1;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[3].second = newPos3y;

		rotationPos = 2;
	}
	else if (rotationPos == 2)
	{
		if (Positions[3].first > 18) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 2;
		int newPos0y = currPos0y + 2;

		int newPos1x = currPos1x - 1;
		int newPos1y = currPos1y + 1;

		int newPos2x = currPos2x;
		int newPos2y = currPos2y;

		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[3].second = newPos3y;

		rotationPos = 1;
	}
}


void Tetromino::RotateJ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second > 8) return;


		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y + 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x - 1;
		int newPos2y = currPos2y - 1;

		int newPos3x = currPos3x - 2;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
	//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 2;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].first > 18) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y - 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x - 1;
		int newPos2y = currPos2y + 1;

		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 2;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 3;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 1;
		int newPos0y = currPos0y - 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y + 1;

		int newPos3x = currPos3x + 2;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 4;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].first < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 1;
		int newPos0y = currPos0y + 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y - 1;

		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 2;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 1;
	}
}

void Tetromino::RotateL(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second < 1) return;


		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y + 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x - 1;
		int newPos2y = currPos2y - 1;

		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 2;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 2;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].first < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y - 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x - 1;
		int newPos2y = currPos2y + 1;

		int newPos3x = currPos3x - 2;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 3;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 1;
		int newPos0y = currPos0y - 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y + 1;

		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 2;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 4;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].first > 18) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 1;
		int newPos0y = currPos0y + 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y - 1;

		int newPos3x = currPos3x + 2;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 1;
	}
}


void Tetromino::RotateT(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].first < 1) return;


		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 1;
		int newPos0y = currPos0y + 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y - 1;

		int newPos3x = currPos3x - 1;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 2;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y + 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x - 1;
		int newPos2y = currPos2y +-1;

		int newPos3x = currPos3x - 1;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
	//	if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
	//	if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 3;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].first > 18) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y - 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x - 1;
		int newPos2y = currPos2y + 1;

		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
	//	if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


	//	dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
	//	dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
	//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 4;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 1;
		int newPos0y = currPos0y - 1;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y;

		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y + 1;

		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
	//	if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
	//	if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


	//	dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
	//	dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 1;
	}
}


void Tetromino::RotateS(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].first < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y ;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;

		int newPos2x = currPos2x - 1;
		int newPos2y = currPos2y;

		int newPos3x = currPos3x - 2;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


	//	dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
	//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 2;
	}
	else if (rotationPos == 2)
	{
		if (Positions[2].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 1;
		int newPos0y = currPos0y;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;

		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;

		int newPos3x = currPos3x + 2;
		int newPos3y = currPos3y - 1;

	//	if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
	//	if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
	//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 1;
	}
}


void Tetromino::RotateZ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].first < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x - 1;
		int newPos0y = currPos0y + 2;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;

		int newPos2x = currPos2x - 1;
		int newPos2y = currPos2y;

		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 2;
	}
	else if (rotationPos == 2)
	{
		if (Positions[2].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y - 2;

		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;

		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;

		int newPos3x = currPos3x ;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//	if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
	//	if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
			//	dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;

		rotationPos = 1;
	}
}

void Tetromino::LeftI(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}


void Tetromino::LeftO(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (Positions[0].second < 1) return;

	int currPos0x = Positions[0].first;
	int currPos0y = Positions[0].second;
	int currPos1x = Positions[1].first;
	int currPos1y = Positions[1].second;
	int currPos2x = Positions[2].first;
	int currPos2y = Positions[2].second;
	int currPos3x = Positions[3].first;
	int currPos3y = Positions[3].second;

	int newPos0x = currPos0x;
	int newPos0y = currPos0y - 1;
	int newPos1x = currPos1x;
	int newPos1y = currPos1y - 1;
	int newPos2x = currPos2x;
	int newPos2y = currPos2y - 1;
	int newPos3x = currPos3x;
	int newPos3y = currPos3y - 1;

	if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
	//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
	if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
	//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


	//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
	//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
	dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


	dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
//	dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
//	dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

	Positions[0].first = newPos0x;
	Positions[1].first = newPos1x;
	Positions[2].first = newPos2x;
	Positions[3].first = newPos3x;
	Positions[0].second = newPos0y;
	Positions[1].second = newPos1y;
	Positions[2].second = newPos2y;
	Positions[3].second = newPos3y;
}

void Tetromino::LeftJ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[3].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::LeftL(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[2].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[3].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::LeftT(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[3].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[2].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::LeftS(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[3].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::LeftZ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


	//	dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
	//	dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
	//	dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
	//	dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[2].second < 1) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y - 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y - 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y - 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y - 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::RightI(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[3].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::RightO(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (Positions[1].second > 8) return;

	int currPos0x = Positions[0].first;
	int currPos0y = Positions[0].second;
	int currPos1x = Positions[1].first;
	int currPos1y = Positions[1].second;
	int currPos2x = Positions[2].first;
	int currPos2y = Positions[2].second;
	int currPos3x = Positions[3].first;
	int currPos3y = Positions[3].second;

	int newPos0x = currPos0x;
	int newPos0y = currPos0y + 1;
	int newPos1x = currPos1x;
	int newPos1y = currPos1y + 1;
	int newPos2x = currPos2x;
	int newPos2y = currPos2y + 1;
	int newPos3x = currPos3x;
	int newPos3y = currPos3y + 1;

//	if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
	if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
//	if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
	if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


	dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
//	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
	dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
//	dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


//	dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
	dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
	dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

	Positions[0].first = newPos0x;
	Positions[1].first = newPos1x;
	Positions[2].first = newPos2x;
	Positions[3].first = newPos3x;
	Positions[0].second = newPos0y;
	Positions[1].second = newPos1y;
	Positions[2].second = newPos2y;
	Positions[3].second = newPos3y;
}

void Tetromino::RightJ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[3].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[2].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::RightL(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[2].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::RightT(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[2].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[3].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::RightS(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

void Tetromino::RightZ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
	//	dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
	//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].second > 8) return;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x;
		int newPos0y = currPos0y + 1;
		int newPos1x = currPos1x;
		int newPos1y = currPos1y + 1;
		int newPos2x = currPos2x;
		int newPos2y = currPos2y + 1;
		int newPos3x = currPos3x;
		int newPos3y = currPos3y + 1;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
}

bool Tetromino::DownI(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	return true;
}

bool Tetromino::DownO(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (Positions[3].first > 18) return false;

	int currPos0x = Positions[0].first;
	int currPos0y = Positions[0].second;
	int currPos1x = Positions[1].first;
	int currPos1y = Positions[1].second;
	int currPos2x = Positions[2].first;
	int currPos2y = Positions[2].second;
	int currPos3x = Positions[3].first;
	int currPos3y = Positions[3].second;

	int newPos0x = currPos0x + 1;
	int newPos0y = currPos0y;
	int newPos1x = currPos1x + 1;
	int newPos1y = currPos1y;
	int newPos2x = currPos2x + 1;
	int newPos2y = currPos2y;
	int newPos3x = currPos3x + 1;
	int newPos3y = currPos3y;

	//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
	//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
	if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
	if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


	dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
	dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
	//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
	//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


	//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
	//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
	dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

	Positions[0].first = newPos0x;
	Positions[1].first = newPos1x;
	Positions[2].first = newPos2x;
	Positions[3].first = newPos3x;
	Positions[0].second = newPos0y;
	Positions[1].second = newPos1y;
	Positions[2].second = newPos2y;
	Positions[3].second = newPos3y;
	
	return true;
}

bool Tetromino::DownJ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	return true;
}

bool Tetromino::DownL(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[2].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) { 
			return false; }
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) { 
			return false; }


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[3].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	return true;
}

bool Tetromino::DownT(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[2].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 3)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 4)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	return true;
}

bool Tetromino::DownS(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	return true;
}

bool Tetromino::DownZ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[3].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return false;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}
	else if (rotationPos == 2)
	{
		if (Positions[0].first > 18) return false;

		int currPos0x = Positions[0].first;
		int currPos0y = Positions[0].second;
		int currPos1x = Positions[1].first;
		int currPos1y = Positions[1].second;
		int currPos2x = Positions[2].first;
		int currPos2y = Positions[2].second;
		int currPos3x = Positions[3].first;
		int currPos3y = Positions[3].second;

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return false;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return false;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take(Color);
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take(Color);
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take(Color);

		Positions[0].first = newPos0x;
		Positions[1].first = newPos1x;
		Positions[2].first = newPos2x;
		Positions[3].first = newPos3x;
		Positions[0].second = newPos0y;
		Positions[1].second = newPos1y;
		Positions[2].second = newPos2y;
		Positions[3].second = newPos3y;
	}

	return true;
}


