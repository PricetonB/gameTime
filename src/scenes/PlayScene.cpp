#include "PlayScene.h"
#include <iostream>
#include <limits>



PlayScene::PlayScene(sf::RenderWindow& win) : Scene(win) {}


// Inherited: sf::RenderWindow& window

//private methods
void PlayScene::_changeScene(std::string sceneName) {
    _sceneChangeNeeded = true;
    _sceneToChangeTo = sceneName;
}


//public methods
void PlayScene::update() {
    std::cout << "in play scene type menu to return to menu\n";
    std::string nextScene;
    std::cin >> nextScene;
    if (nextScene != "menu" && nextScene != "multiplayer") {
        std::cout << "scene not recognized \n";
    } else {
        _changeScene(nextScene);
    }
}

std::string PlayScene::nextScene() {
    return _sceneChangeNeeded ? _sceneToChangeTo : "";
}


