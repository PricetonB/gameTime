#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Scene.h"
#include <string>


//--------------------

class PlayScene : public Scene {
    //private members
    bool _sceneChangeNeeded = false;
    std::string _sceneToChangeTo = "";

    //private methods
    void _changeScene(std::string sceneName);

public:
    //constructor
    PlayScene(sf::RenderWindow& win);

    //public methods
    void update() override;
    std::string nextScene() override;
};

#endif


