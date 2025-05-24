#include "PlayScene.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>



PlayScene::PlayScene(sf::RenderWindow& win) : Scene(win) {
	Init(_configFile);
}


// Inherited: sf::RenderWindow& window

//private methods
void PlayScene::_changeScene(std::string sceneName) {
    _sceneChangeNeeded = true;
    _sceneToChangeTo = sceneName;
}

//--------------------------------------------


void PlayScene::Init(const std::string& _configFile)
{
	GameFrameCount = 0;
	IsRunning = true;
	
	//Read in the config file 
	std::fstream input{ _configFile };

	if (!input.is_open())
	{
        std::cout << "Current path: " << std::filesystem::current_path() << '\n';
		std::cerr << "Failed to open: " << _configFile << '\n';
		exit(-1);
	}

	//get data from txt file and assign to variables
	std::string identifier;

	while (input >> identifier) {

		if (identifier == "Player") {
			input >> PlayerSpecs.ShapeRadius;
			input >> PlayerSpecs.CollisionRadius;
			input >> PlayerSpecs.Speed;

			// Read color values as int, then cast to uint8_t
			int r, g, b;
			input >> r;
			input >> g;
			input >> b;
			PlayerSpecs.FillColor.r = static_cast<uint8_t>(r);
			PlayerSpecs.FillColor.g = static_cast<uint8_t>(g);
			PlayerSpecs.FillColor.b = static_cast<uint8_t>(b);

			input >> r;
			input >> g;
			input >> b;
			PlayerSpecs.OutlineColor.r = static_cast<uint8_t>(r);
			PlayerSpecs.OutlineColor.g = static_cast<uint8_t>(g);
			PlayerSpecs.OutlineColor.b = static_cast<uint8_t>(b);


			input >> PlayerSpecs.OutlineThickness;
			input >> PlayerSpecs.ShapeVertices;
		}
		else if (identifier == "Bullet") {
			input >> BulletSpecs.ShapeRadius;
			input >> BulletSpecs.CollisionRadius;
			input >> BulletSpecs.Speed;
			// Read color values as int, then cast to uint8_t
			int r, g, b;
			input >> r;
			input >> g;
			input >> b;
			BulletSpecs.FillColor.r = static_cast<uint8_t>(r);
			BulletSpecs.FillColor.g = static_cast<uint8_t>(g);
			BulletSpecs.FillColor.b = static_cast<uint8_t>(b);

			input >> r;
			input >> g;
			input >> b;
			BulletSpecs.OutlineColor.r = static_cast<uint8_t>(r);
			BulletSpecs.OutlineColor.g = static_cast<uint8_t>(g);
			BulletSpecs.OutlineColor.b = static_cast<uint8_t>(b);


			input >> BulletSpecs.OutlineThickness;
			input >> BulletSpecs.ShapeVertices;
			input >> BulletSpecs.LifeSpan;
		}


	}
	SpawnPlayer();
	std::cout << "spawn interval: " << EnemySpecs.SpawnInterval << "\n";
}

//--------------------------------------------


void PlayScene::SpawnPlayer()
{
	//This goes slightly against the EntityManagers paradigm
	Player = EntityManager.AddEntity("Player");

	sf::Vector2f middleOfWindow{ window.getSize().x / 2.0f, window.getSize().y / 2.0f };

	Player->cTransform = std::make_shared<CTransform>(middleOfWindow, sf::Vector2f(0.0f, 0.0f), 0.0f);
	Player->cShape = std::make_shared<CShape>(PlayerSpecs.ShapeRadius, PlayerSpecs.ShapeVertices,
	PlayerSpecs.FillColor, PlayerSpecs.OutlineColor, PlayerSpecs.OutlineThickness);
	Player->cCollision = std::make_shared<CCollision>(PlayerSpecs.CollisionRadius);
	Player->cInput = std::make_shared<CInput>();
	Player->cSpecialShoot = std::make_shared<CSpecialShoot>(40, 60 * 10);
	Player->cShoot = std::make_shared<CShoot>(10);
}

//--------------------------------------------



void PlayScene::SpawnBullet(const float angle)
{
	auto bullet = EntityManager.AddEntity("Bullet");
	bullet->cShape = std::make_shared<CShape>(BulletSpecs.ShapeRadius, BulletSpecs.ShapeVertices,
		BulletSpecs.FillColor, BulletSpecs.OutlineColor, BulletSpecs.OutlineThickness);
	bullet->cCollision = std::make_shared<CCollision>(BulletSpecs.CollisionRadius);
	bullet->cLifeSpan = std::make_shared<CLifeSpan>(BulletSpecs.LifeSpan);

	auto velX = std::cos(angle) * BulletSpecs.Speed;
	auto velY = std::sin(angle) * BulletSpecs.Speed;
	sf::Vector2f shapeVel{ velX,  velY };
	bullet->cTransform = std::make_shared<CTransform>(Player->cTransform->Position, shapeVel, angle);

}

//--------------------------------------------



void PlayScene::sMovement()
{
	if (Player->cInput->Down) {
		Player->cTransform->Velocity.y = PlayerSpecs.Speed;
	}
	else if (Player->cInput->Up) {
		Player->cTransform->Velocity.y = -PlayerSpecs.Speed;
	}
	else {
		Player->cTransform->Velocity.y = 0;
	}

	if (Player->cInput->Right) {
		Player->cTransform->Velocity.x = PlayerSpecs.Speed;
	}
	else if (Player->cInput->Left) {
		Player->cTransform->Velocity.x = -PlayerSpecs.Speed;
	}
	else {
		Player->cTransform->Velocity.x = 0;
	}

	for (auto& e : EntityManager.GetEntities()) {
		if (e->cTransform != nullptr)
		{
			e->cTransform->Position.x += e->cTransform->Velocity.x;
			e->cTransform->Position.y += e->cTransform->Velocity.y;

		}
	}
}

//--------------------------------------------


void PlayScene::sRender()
{
	window.clear();

	for (auto& e : EntityManager.GetEntities()) {
		if (e->cShape != nullptr)
		{
			e->cTransform->Angle += 1;

			e->cShape->Shape.setPosition(e->cTransform->Position);
			e->cShape->Shape.setRotation(sf::degrees(e->cTransform->Angle));
			window.draw(e->cShape->Shape);
		}
	}
	window.display();
}

//--------------------------------------------


void PlayScene::sSpawner()
{
	return;
}


//--------------------------------------------


void PlayScene::sUserInput()
{
	//reset mouse input
	Player->cInput->LeftClick = false;
	Player->cInput->RightClick = false;

	//check for events
	while (auto event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>()) {
			window.close();
			continue;
		}

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			using Scan = sf::Keyboard::Scancode;

			switch (keyPressed->scancode) {
			case Scan::Escape:
				window.close();
				break;
			case Scan::W:
				Player->cInput->Up = true;
				break;
			case Scan::A:
				Player->cInput->Left = true;
				break;
			case Scan::S:
				Player->cInput->Down = true;
				break;
			case Scan::D:
				Player->cInput->Right = true;
				break;
			case Scan::P:
				IsRunning = !IsRunning;
				break;
			default:
				break;
			}
		}

		if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
			using Scan = sf::Keyboard::Scancode;

			switch (keyReleased->scancode) {
			case Scan::W:
				Player->cInput->Up = false;
				break;
			case Scan::A:
				Player->cInput->Left = false;
				break;
			case Scan::S:
				Player->cInput->Down = false;
				break;
			case Scan::D:
				Player->cInput->Right = false;
				break;
			default:
				break;
			}
		}

		if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
			if (!IsRunning) continue;

			switch (mousePressed->button) {
			case sf::Mouse::Button::Left:
				Player->cInput->LeftClick = true;
				Player->cInput->MousePos = sf::Vector2f(
					static_cast<float>(mousePressed->position.x),
					static_cast<float>(mousePressed->position.y)
				);
				break;
			case sf::Mouse::Button::Right:
				Player->cInput->RightClick = true;
				break;
			default:
				break;
			}
		}
	}
}


//TODO make shoot and special shoot into one function later


void PlayScene::sSpecialShoot()
{
	if (Player->cInput->RightClick) {
		if (Player->cSpecialShoot->RemainingCooldown == 0) {
			// spawn many bullet
			for (size_t i = 0; i < Player->cSpecialShoot->BulletAmount; i++)
			{
				float angle = (360.0f / Player->cSpecialShoot->BulletAmount) * i;
				SpawnBullet(angle);
			}

			// set up cooldown
			Player->cSpecialShoot->RemainingCooldown = Player->cSpecialShoot->Cooldown;
		}
	}

	if (Player->cSpecialShoot->RemainingCooldown > 0) {
		Player->cSpecialShoot->RemainingCooldown--;
	}


}


void PlayScene::sShoot()
{
	if (Player->cInput->LeftClick) {

		if (Player->cShoot->RemainingCooldown == 0) {
			// spawn bullet
			auto playerX = Player->cTransform->Position.x;
			auto playerY = Player->cTransform->Position.y;
			auto diffX = Player->cInput->MousePos.x - playerX;
			auto diffY = Player->cInput->MousePos.y - playerY;
			auto angle = std::atan2(diffY, diffX);
			SpawnBullet(angle);

			// set up cooldown
			Player->cShoot->RemainingCooldown = Player->cShoot->Cooldown;
		}
	}

	if (Player->cShoot->RemainingCooldown > 0) {
		Player->cShoot->RemainingCooldown--;
	}


}








//==============================================================



//public methods
void PlayScene::update() {

	while (window.isOpen()) {


		ManuelSpawnFlag = true;

		sUserInput();

		if (IsRunning) {
			GameFrameCount++;
			EntityManager.Update();
			sSpawner();
			sMovement();
			sRender();
		}
	}

}


//--------------------------------------------



std::string PlayScene::nextScene() {
    return _sceneChangeNeeded ? _sceneToChangeTo : "";
}



//============================================================
//ORIGINAL COPY 

/*

PlayScene::PlayScene(sf::RenderWindow& win) : Scene(win) {}


// Inherited: sf::RenderWindow& window

//private methods
void PlayScene::_changeScene(std::string sceneName) {
    _sceneChangeNeeded = true;
    _sceneToChangeTo = sceneName;
}


//public methods
void PlayScene::update() {
    std::cout << "in play scene type menu to return to menu\n";
    std::string nextScene;
    std::cin >> nextScene;
    if (nextScene != "menu" && nextScene != "multiplayer") {
        std::cout << "scene not recognized \n";
    } else {
        _changeScene(nextScene);
    }
}

std::string PlayScene::nextScene() {
    return _sceneChangeNeeded ? _sceneToChangeTo : "";
}

*/



