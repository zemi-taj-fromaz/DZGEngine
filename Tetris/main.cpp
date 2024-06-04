#include<iostream>

#include "MyScene.h"

std::unique_ptr<Scene> CreateScene()
{
	return std::unique_ptr<Scene>(new MyScene(600u, 800u));
}

#include <EntryPoint.h>