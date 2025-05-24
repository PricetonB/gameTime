#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Scene.h"
#include <string>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "fileStructs.h"





//--------------------

class PlayScene : public Scene {

    // Inherited: sf::RenderWindow& window

	
    //private members
    bool _sceneChangeNeeded = false;
    std::string _sceneToChangeTo = "";
    std::string _configFile = "../../config.txt";
    EntityManagerCls EntityManager;
    
    PlayerSpecsStr PlayerSpecs;
    EnemySpecsStr EnemySpecs;
    BulletSpecsStr BulletSpecs;
    
    EntityPtr Player;
    
    size_t GameScore;
    
    size_t GameFrameCount;
    
    sf::Clock DeltaClock;
    
    uint16_t SpawnInterval;
    bool ManuelSpawnFlag;
    
    bool IsPaused;
    bool IsRunning;
    

    //private methods
    void _changeScene(std::string sceneName);
    void Init(const std::string& _configFile);
    
    void SpawnPlayer();
    void SpawnEnemy();
    void SpawnBullet(const float angle);
    void SpawnSmallEnemy(std::shared_ptr<EntityCls> deadEnemy);
    
    void sMovement();
    void sRender();
    void sSpawner();
    void sCollision();
    void sUserInput();
    void sLifeSpan();
    void sSpecialShoot();
    void sShoot();
    

public:
    //constructor
    PlayScene(sf::RenderWindow& win);

    //public methods
    void update() override;
    std::string nextScene() override;
};

#endif




//-------------------------------------------------------------
//-------------------------------------------------------------









