#include "Tetromino.h"

#include "Field.h"

void Tetromino::processDown(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (type == TetrominoType::I) DownI(MeshVec);
	else if (type == TetrominoType::J) DownJ(MeshVec);
	else if (type == TetrominoType::L) DownL(MeshVec);
	else if (type == TetrominoType::T) DownT(MeshVec);
	else if (type == TetrominoType::S) DownS(MeshVec);
	else if (type == TetrominoType::Z) DownZ(MeshVec);

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
}
void Tetromino::processRight(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (type == TetrominoType::I) RightI(MeshVec);
	else if (type == TetrominoType::J) RightJ(MeshVec);
	else if (type == TetrominoType::L) RightL(MeshVec);
	else if (type == TetrominoType::T) RightT(MeshVec);
	else if (type == TetrominoType::S) RightS(MeshVec);
	else if (type == TetrominoType::Z) RightZ(MeshVec);
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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
	//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
	//	dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
	//	dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
	//	dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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

void Tetromino::DownI(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
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
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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

void Tetromino::DownJ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
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
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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

void Tetromino::DownL(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
	{
		if (Positions[2].first > 18) return;

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
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		if (Positions[3].first > 18) return;

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

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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

void Tetromino::DownT(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
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

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		if (Positions[2].first > 18) return;

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
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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

void Tetromino::DownS(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
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

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		//dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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

void Tetromino::DownZ(std::vector<std::shared_ptr<Mesh>>& MeshVec)
{
	if (rotationPos == 1)
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

		int newPos0x = currPos0x + 1;
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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
		int newPos0y = currPos0y;
		int newPos1x = currPos1x + 1;
		int newPos1y = currPos1y;
		int newPos2x = currPos2x + 1;
		int newPos2y = currPos2y;
		int newPos3x = currPos3x + 1;
		int newPos3y = currPos3y;

		//if (dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->IsTaken()) return;
		//if (dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->IsTaken()) return;
		if (dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->IsTaken()) return;


		dynamic_cast<Field*>(MeshVec[currPos0x * 10 + currPos0y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos1x * 10 + currPos1y].get())->Free();
		dynamic_cast<Field*>(MeshVec[currPos2x * 10 + currPos2y].get())->Free();
		//dynamic_cast<Field*>(MeshVec[currPos3x * 10 + currPos3y].get())->Free();


		//dynamic_cast<Field*>(MeshVec[newPos0x * 10 + newPos0y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos1x * 10 + newPos1y].get())->Take();
		//dynamic_cast<Field*>(MeshVec[newPos2x * 10 + newPos2y].get())->Take();
		dynamic_cast<Field*>(MeshVec[newPos3x * 10 + newPos3y].get())->Take();

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


