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

    virtual void update(float totalTime, float deltaTime, dzg* app) override;
 
    float Speed;

private:
    void load_pillar();
    

};

