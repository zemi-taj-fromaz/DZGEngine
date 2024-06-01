#pragma once
#include "Mesh.h"
#include "app/app.h"
#include <random>

struct Pillar : public Mesh
{
    Pillar()
    {
        load_pillar();
    }

    virtual void update(float totalTime, float deltaTime, dzg* app) override
    {
        offsetPosition(glm::vec3(-4.0f * deltaTime, 0.0f, 0.0f));
        
        if (Position.x < app->camera->left - 1.0f)
        {
            offsetPosition(glm::vec3(8 * 8.0f, 0.0f, 0.0f));
        }
    }


private:
    void load_pillar();

};

