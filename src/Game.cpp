#include "Game.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "MultiplayerScene.h"

#include <iostream>
#include <memory>
#include <fstream>
//#include <sstream>
//#include <stdio.h>
#include <filesystem>


Game::Game(const std::string& configFile) {
    init(configFile);
    currentScene = createScene("menu");
}

std::unique_ptr<Scene> Game::createScene(const std::string& name) {
    std::cout << "in game changing to: " << name << "\n";
    if (name == "menu") return std::make_unique<MenuScene>(Window);
    if (name == "play") return std::make_unique<PlayScene>(Window);
    if (name == "multiplayer") return std::make_unique<MultiplayerScene>(Window);
    return nullptr;
}

void Game::run() {
    while (Window.isOpen() && currentScene) {
        currentScene->update();
        std::string next = currentScene->nextScene();
        if (!next.empty()) {
            std::cout << "calling current scene in game run due to next empty" "\n";
            currentScene = createScene(next);
            
        }
    }
}

void Game::init(const std::string& configFile)
{
        GameFrameCount = 0;
        IsRunning = true;

        //Read in the config file 
        std::fstream input{ configFile };

        if (!input.is_open())
        {
        std::cout << "Current path: " << std::filesystem::current_path() << '\n';
                std::cerr << "Failed to open: " << configFile << '\n';
                exit(-1);
        }

        //get data from txt file and assign to variables
        std::string identifier;

        while (input >> identifier) {
                if (identifier == "Window")
                {
                        unsigned int width;
                        input >> width;

                        unsigned int height;
                        input >> height;

                        unsigned int fps;
                        input >> fps;

                        int fullscreen;
                        input >> fullscreen;

                        if (fullscreen == 1) {
                                Window.create(sf::VideoMode({width, height}), "Space War", sf::State::Windowed);
                        }
                        else {
                                auto fullScreenModes = sf::VideoMode::getFullscreenModes();
                                Window.create(fullScreenModes[0], "Space Wars", sf::State::Fullscreen);
                        }
                        // bullshit fps = 1;
                        Window.setFramerateLimit(fps);
                }
	}

}










