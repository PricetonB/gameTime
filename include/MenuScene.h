#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "Scene.h"
#include <string>

class MenuScene : public Scene {
    //private members
    bool _sceneChangeNeeded = false;
    std::string _sceneToChangeTo = "";

    //private methods
    void _changeScene(std::string sceneName);

public:
    //constructor
    MenuScene(sf::RenderWindow& win);

    //public methods
    void update() override;
    std::string nextScene() override;
};

#endif

