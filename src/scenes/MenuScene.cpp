#include "MenuScene.h"
#include <iostream>


MenuScene::MenuScene(sf::RenderWindow& win) : Scene(win) {}

// Inherited: sf::RenderWindow& window

//private methods
void MenuScene::_changeScene(std::string sceneName) {
    _sceneChangeNeeded = true;
    _sceneToChangeTo = sceneName;
}


//public methods
void MenuScene::update() {
    std::cout << "what scene do you want to go to, play or multiplayer\n";
    std::string nextScene;
    std::cin >> nextScene;
    if (nextScene != "play" && nextScene != "multiplayer") {
        std::cout << "scene not recognized \n";
    } else {
        _changeScene(nextScene);
    }
}

std::string MenuScene::nextScene() {
    return _sceneChangeNeeded ? _sceneToChangeTo : "";
}

