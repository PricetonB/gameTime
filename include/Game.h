#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class Game {
    std::unique_ptr<Scene> currentScene;
    std::unique_ptr<Scene> createScene(const std::string& name);
    sf::RenderWindow Window;

    size_t GameFrameCount;
    bool IsRunning;

public:
    Game(const std::string& configFile);
    void init(const std::string& configFile);
    void run();
};

#endif

