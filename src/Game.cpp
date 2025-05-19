#include "Game.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "MultiplayerScene.h"

Game::Game() {
    currentScene = createScene("menu");
}

std::unique_ptr<Scene> Game::createScene(const std::string& name) {
    if (name == "menu") return std::make_unique<MenuScene>();
    if (name == "play") return std::make_unique<PlayScene>();
    if (name == "multiplayer") return std::make_unique<MultiplayerScene>();
    return nullptr;
}

void Game::run() {
    while (currentScene) {
        currentScene->update();
        std::string next = currentScene->nextScene();
        if (!next.empty()) {
            currentScene = createScene(next);
        }
    }
}

