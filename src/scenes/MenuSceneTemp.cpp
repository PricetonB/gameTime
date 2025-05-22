#include "MenuScene.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>



MenuScene::MenuScene(sf::RenderWindow& win) : Scene(win) {
	Init(_configFile);
}


// Inherited: sf::RenderWindow& window

//private methods
void MenuScene::_changeScene(std::string sceneName) {
    _sceneChangeNeeded = true;
    _sceneToChangeTo = sceneName;
}

//--------------------------------------------


void MenuScene::Init(const std::string& _configFile)
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



		if (identifier == "SinglePlayerButton") {
			input >> SinglePlayerButtonSpecs.Width;
		        input >> SinglePlayerButtonSpecs.Height;
			input >> SinglePlayerButtonSpecs.X
			input >> SinglePlayerButtonSpecs.Y;
			input >> SinglePlayerButtonSpecs.OutlineThickness
	        	int r, g, b;
			input >> r;
			input >> g;
			input >> b;
			SinglePlayerButtonSpecs.FillColor.r = static_cast<uint8_t>(r);
			SinglePlayerButtonSpecs.FillColor.g = static_cast<uint8_t>(g);
			SinglePlayerButtonSpecs.FillColor.b = static_cast<uint8_t>(b);
			input >> r;
			input >> g;
			input >> b;
			SinglePlayerButtonSpecs.OutlineColor.r = static_cast<uint8_t>(r);
			SinglePlayerButtonSpecs.OutlineColor.g = static_cast<uint8_t>(g);
			SinglePlayerButtonSpecs.OutlineColor.b = static_cast<uint8_t>(b);




		
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


void MenuScene::SpawnMenuButtons() {
	SpawnButton(SinglePlayerButtonSpecs.Width, SinglePlayerButtonSpecs.Height, SinglePlayerButtonSpecs.X, SinglePlayerButtonSpecs.Y,
			SinglePlayerButtonSpecs.OutlineThickness, SinglePlayerSpecs.OutlineColor, SinglePlayerSpecs.FillColor );

	//TODO call spawn button for multiplayer button and add struct etc. `


}

//--------------------------------------------


void MenuScene::SpawnButton(float width, float height, float  x, float y, float outlineThickness, sf::Color outlineColor, fillColor ) 
{

	auto button = EntityManager.AddEntity("Button");
	
	sf::Vector2f rectanglePosition{ x, y };
	button->cTransform = std::make_shared<CTransform>(rectanglePosition, sf::Vector2f(0.0f, 0.0f), 0.0f);
	button->cRectangle = std::make_shared<CRectangle>(width, height, outlineThickness, outlineColor, fillColor) 



//---------------------------------------------

//TODO this is staying as reference for movement system being used to implement what happens when buttons are clicked since it used players cinput
//either change this function to not make the shape and just have player object or create another thing that can hold cinput. thats really all this is for is cinput
void MenuScene::SpawnPlayer()
{
	//This goes slightly against the EntityManagers paradigm
	Player = EntityManager.AddEntity("Player");

	sf::Vector2f middleOfWindow{ window.getSize().x / 2.0f, window.getSize().y / 2.0f };

	Player->cTransform = std::make_shared<CTransform>(middleOfWindow, sf::Vector2f(0.0f, 0.0f), 0.0f);
	Player->cShape = std::make_shared<CShape>(PlayerSpecs.ShapeRadius, PlayerSpecs.ShapeVertices, PlayerSpecs.FillColor, PlayerSpecs.OutlineColor, PlayerSpecs.OutlineThickness);
	Player->cCollision = std::make_shared<CCollision>(PlayerSpecs.CollisionRadius);
	Player->cInput = std::make_shared<CInput>();
	Player->cSpecialShoot = std::make_shared<CSpecialShoot>(40, 60 * 10);
}

//--------------------------------------------


void MenuScene::sMovement()
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

//TODO why the fuck is render system updating positions and rotating shapes. seems like it should just focus on drawing shapes and sprites
//also thi will update the sf shapes position and rotation even if it has not changed. seems weird for shapes that never move in menu screen
//makes much more sense in gameplay so maybe leave it alone
//
//actually im stupid the movement system updates the transform this just sends the updated trasnform to the sf shape before render:
void MenuScene::sRender()
{
	window.clear();

	for (auto& e : EntityManager.GetEntities()) {
		if (e->cShape != nullptr)
		{
			e->cTransform->Angle += 1;

			//Shape is sf::shape and we are using sfml set position and rotation functions here
			e->cShape->Shape.setPosition(e->cTransform->Position);
			e->cShape->Shape.setRotation(sf::degrees(e->cTransform->Angle));
			window.draw(e->cShape->Shape);
		}

		if (e->cRectangle != nullptr)
		{
			e->cRectangle->Rectangle.setPosition(e->cTransform->Position);
			e->cRectangle->Shape.setRotation(sf::degrees(e->cTransform->Angle));
			window.draw(e->cShape->Shape);
			

		}
	}
	window.display();
}

//--------------------------------------------


void MenuScene::sSpawner()
{
//TODO this shoot needs to be changed to left and right click in actual play scene. 
//this should not set the left and right click to false. need to make something 
//in this that will know the difference if mouse is down or clicked. it should only shoot
//on clicked not on mouse down. maybe while cInput.leftMouseDown go into shoot bypass mode 
//or just recognize the click instead of mouse being held down.
//theres also a special shoot component maybe figure out where that is getting done and do shoot similar

	if (Player->cInput->Shoot) {
		Player->cInput->Shoot = false;
		auto playerX = Player->cTransform->Position.x;
		auto playerY = Player->cTransform->Position.y;

		auto diffX = Player->cInput->MousePos.x - playerX;
		auto diffY = Player->cInput->MousePos.y - playerY;

		auto angle = std::atan2(diffY, diffX);

		SpawnBullet(angle);

	}

}


//--------------------------------------------


void MenuScene::sUserInput()
{
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
				Player->cInput->Shoot = true;
				Player->cInput->MousePos = sf::Vector2f(
					static_cast<float>(mousePressed->position.x),
					static_cast<float>(mousePressed->position.y)
				);
				break;
			case sf::Mouse::Button::Right:
				Player->cInput->SpecialShoot = true;
				break;
			default:
				break;
			}
		}
	}
}





//==============================================================



//public methods
void MenuScene::update() {

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



std::string MenuScene::nextScene() {
    return _sceneChangeNeeded ? _sceneToChangeTo : "";
}



//============================================================
//ORIGINAL COPY 

/*

MenuScene::MenuScene(sf::RenderWindow& win) : Scene(win) {}


// Inherited: sf::RenderWindow& window

//private methods
void MenuScene::_changeScene(std::string sceneName) {
    _sceneChangeNeeded = true;
    _sceneToChangeTo = sceneName;
}


//public methods
void MenuScene::update() {
    std::cout << "in play scene type menu to return to menu\n";
    std::string nextScene;
    std::cin >> nextScene;
    if (nextScene != "menu" && nextScene != "multiplayer") {
        std::cout << "scene not recognized \n";
    } else {
        _changeScene(nextScene);
    }
}

std::string MenuScene::nextScene() {
    return _sceneChangeNeeded ? _sceneToChangeTo : "";
}

*/




