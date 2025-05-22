#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "Scene.h"
#include <string>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "EntityManager.h"



struct MinMaxFStr {
	float Min;
	float Max;
};

struct MinMaxIStr {
	size_t Min;
	size_t Max;
};

struct PlayerSpecsStr {
	uint16_t ShapeRadius;
	uint16_t CollisionRadius;
	float Speed;
	sf::Color FillColor;
	sf::Color OutlineColor;
	uint16_t OutlineThickness;
	size_t ShapeVertices;

};

struct EnemySpecsStr {
	uint16_t ShapeRadius;
	uint16_t CollisionRadius;
	MinMaxFStr Speed;
	sf::Color OutlineColor;
	uint16_t OutlineThickness;
	MinMaxIStr ShapeVertices;
	uint16_t LifeSpan;
	uint16_t SpawnInterval;
};

struct BulletSpecsStr {
	uint16_t ShapeRadius;
	uint16_t CollisionRadius;
	float Speed;
	sf::Color FillColor;
	sf::Color OutlineColor;
	uint16_t OutlineThickness;
	size_t ShapeVertices;
	uint16_t LifeSpan;
};


struct SinglePlayerButtonSpecsStr {
	uint16_t Width;
	uint16_t Height;
	uint16_t X;
	uint16_t Y;
	uint16_t OutlineThickness;
	sf::Color OutlineColor;
	sf::Color FillColor;
}



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

    SinglePlayerButtonSpecsStr SinglePlayerButtonSpecs;
    
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
    
    void SpawnMenuButtons();
    void SpawnButton(float width, float height, float  x, float y, float outlineThickness, sf::Color outlineColor, fillColor );



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










