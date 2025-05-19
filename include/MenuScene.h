#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "Scene.h"
#include <string>

class MenuScene : public Scene {
    bool _sceneChangeNeeded = false;
    std::string _sceneToChangeTo = "";

    void _changeScene(std::string sceneName);

public:
    MenuScene(sf::RenderWindow& win);
    void update() override;
    std::string nextScene() override;
};

#endif

