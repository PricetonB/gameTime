#ifndef MULTIPLAYER_SCENE_H
#define MULTIPLAYER_SCENE_H

#include "Scene.h"

class MultiplayerScene : public Scene {
    bool _sceneChangeNeeded = false;
public:
    MultiplayerScene(sf::RenderWindow& wind);
    void update() override;
    std::string nextScene() override;
};

#endif

