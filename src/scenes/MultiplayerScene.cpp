#include "MultiplayerScene.h"
#include <iostream>
#include <limits>


MultiplayerScene::MultiplayerScene(sf::RenderWindow& win) : Scene(win) {}

void MultiplayerScene::update() {
    std::cout << "multiplayer Scene: Press Enter to Return to Menu...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    _sceneChangeNeeded = true;
}

std::string MultiplayerScene::nextScene() {
    return _sceneChangeNeeded ? "menu" : "";
}

