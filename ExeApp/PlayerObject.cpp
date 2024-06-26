#include "PlayerObject.h"

void PlayerObject::load_player()
{

    static std::random_device dev;
    static std::mt19937 rng(dev());

    static std::uniform_real_distribution<> distHeight(4.0, 9.0); // distribution in range [1, 6]
    static std::normal_distribution<> distPos(0.0, 3.0); // distribution in range [1, 6]

    Vertices.clear();
    Indices.clear();

    float gapPos = distPos(rng);
    float gapHeight = distHeight(rng);

    float TopTop = -9.0f;
    float TopBottom = gapPos - gapHeight / 2;

    float BottomTop = gapPos + gapHeight / 2;
    float BottomBottom = 9.0f;

    // m2->offsetPosition(glm::vec3(offset * i, -distPos(rng), 0.0f));

 //    auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, distY(rng), 1.0f));

    Vertices = {
    {{  0.0f, TopBottom}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{  1.0f, TopBottom}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{  1.0f, TopTop}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{  0.0f, TopTop}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

    {{  0.0f, BottomBottom}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{  1.0f, BottomBottom}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{  1.0f, BottomTop}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{  0.0f, BottomTop}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    };


    Indices = {
        0, 1, 2, 2, 3, 0,
        0,0,0,
        4, 5, 6, 6, 7, 4,
    };
}