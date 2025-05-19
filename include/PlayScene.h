#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Scene.h"

class PlayScene : public Scene {
    bool _sceneChangeNeeded = false;
public:
    void update() override;
    std::string nextScene() override;
};

#endif

