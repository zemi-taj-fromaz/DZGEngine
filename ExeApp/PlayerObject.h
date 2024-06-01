#pragma once
#include "Mesh.h"

#include <random>

struct PlayerObject : public Mesh
{
    PlayerObject()
    {
        load_player();
    }

    virtual void update(float totalTime, float deltaTime, dzg* app) override
    {
      //  offsetPosition(glm::vec3(-220000.0f * deltaTime, 0.0f, 0.0f));
    }


private:
    void load_player();


};

