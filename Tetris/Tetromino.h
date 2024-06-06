#pragma once

#include <vector>
#include <memory>
#include <random>

#include <glm/glm.hpp>

struct Mesh;

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
		static std::random_device dev;
		static std::mt19937 rng(dev());
		static std::uniform_int_distribution<int> RandInt(2, 7); // distribution in range [1, 6]

		rotationPos = 1;

		type = Tetromino::GenerateType();
		this->Color = Tetromino::GenerateColor();

		switch (type)
		{
		case(TetrominoType::I):
			{
				float column = RandInt(rng);
				Positions = { {0, column}, {1, column}, {2, column}, {3, column} };
				break;
			}
		case(TetrominoType::J):
		{
			float column = RandInt(rng);
			Positions = { {0, column}, {1, column}, {2, column}, {2, column - 1} };
			break;
		}
		case(TetrominoType::L):
		{
			float column = RandInt(rng);
			Positions = { {0, column}, {1, column}, {2, column}, {2, column + 1} };
			break;
		}
		case(TetrominoType::T):
		{
			float column = RandInt(rng);
			Positions = { {0, column}, {0, column + 1}, {0, column + 2}, {1, column + 1 } };
			break;
		}
		case(TetrominoType::S):
		{
			float column = RandInt(rng);
			Positions = { {0, column}, {0, column - 1}, {1, column - 1}, {1, column - 2} };
			break;
		}
		case(TetrominoType::Z):
		{
			float column = RandInt(rng);
			Positions = { {0, column}, {0, column + 1}, {1, column + 1}, {1, column + 2} };
			break;
		}
		case(TetrominoType::O):
		{
			float column = RandInt(rng);
			Positions = { {0, column}, {0, column + 1}, {1, column}, {1, column + 1} };
			break;
		}
		}
		/* select random Type and select random spawn position(random collumn)*/
	}

	bool processDown(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void processUp(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void processLeft(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void processRight(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	
	bool IsAttached(std::vector<std::shared_ptr<Mesh>>& MeshVec);

	TetrominoType type;
	int rotationPos;
	std::vector<std::pair<int, int> > Positions;
	glm::vec4 Color;

private:

	static std::random_device dev;
	static std::mt19937 rng;

	static std::uniform_int_distribution<int> RandInt; // distribution in range [1, 6]

	static TetrominoType GenerateType();
	static glm::vec4 GenerateColor();


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
	void LeftO(std::vector<std::shared_ptr<Mesh>>& MeshVec);

	void RightI(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightJ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightL(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightT(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightS(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightZ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	void RightO(std::vector<std::shared_ptr<Mesh>>& MeshVec);


	bool DownI(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	bool DownJ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	bool DownL(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	bool DownT(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	bool DownS(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	bool DownZ(std::vector<std::shared_ptr<Mesh>>& MeshVec);
	bool DownO(std::vector<std::shared_ptr<Mesh>>& MeshVec);

};

