#include<iostream>

#include "my_scene.h"

std::unique_ptr<scene> CreateScene()
{
	return std::unique_ptr<scene>(new my_scene());
}

#include <entry_point.h>