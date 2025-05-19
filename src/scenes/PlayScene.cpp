#include "PlayScene.h"
#include <iostream>
#include <limits>


PlayScene::PlayScene(sf::RenderWindow& win) : Scene(win) {}

void PlayScene::update() {
    std::cout << "Play Scene: Press Enter to Return to Menu...\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    _sceneChangeNeeded = true;
}

std::string PlayScene::nextScene() {
    return _sceneChangeNeeded ? "menu" : "";
}

