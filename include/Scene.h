#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <string>

class Scene {
protected:
    sf::RenderWindow& window;  // Reference

public:
    Scene(sf::RenderWindow& win) : window(win) {}
    virtual ~Scene() = default;

    virtual void update() = 0;
    virtual std::string nextScene() = 0;
};

#endif

