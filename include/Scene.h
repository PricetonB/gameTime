#ifndef SCENE_H
#define SCENE_H

#include <string>

class Scene {
public:
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual std::string nextScene() = 0;
};

#endif

