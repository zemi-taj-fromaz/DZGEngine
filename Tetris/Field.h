#pragma once

#pragma once
#include "Mesh.h"
#include "app/app.h"
#include <random>

class Field : public Mesh
{
public:
	Field() : Mesh(MeshType::Quad)
	{
		Color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	}

	void Take() { isTaken = true;  Color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);}
	void Free() { isTaken = false; Color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);}
	bool IsTaken() { return isTaken; }

private:
	bool isTaken = false;
};


