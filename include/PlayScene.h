#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Scene.h"

class PlayScene : public Scene {
    bool _sceneChangeNeeded = false;
public:
    PlayScene(sf::RenderWindow& win);
    void update() override;
    std::string nextScene() override;
};

#endif

