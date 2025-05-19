#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include <memory>
#include <string>

class Game {
    std::unique_ptr<Scene> currentScene;
    std::unique_ptr<Scene> createScene(const std::string& name);

public:
    Game();
    void run();
};

#endif

