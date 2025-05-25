#include "MenuScene.h"
#include <iostream>
//#include <limits>
#include <fstream>
//#include <sstream>
#include <iostream>
#include <filesystem>



MenuScene::MenuScene(sf::RenderWindow& win) : Scene(win) {
	Init(_configFile);
}


// Inherited: sf::RenderWindow& window

//private methods
void MenuScene::_changeScene(std::string sceneName) {
    std::cout << "changing scene in scene change \n";
    _sceneChangeNeeded = true;
    _sceneToChangeTo = sceneName;
    std::cout << "scene change needed: " << _sceneChangeNeeded 
    << "scene to change too: " << _sceneToChangeTo << "\n";
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
			input >> SinglePlayerButtonSpecs.X;
			input >> SinglePlayerButtonSpecs.Y;
			input >> SinglePlayerButtonSpecs.OutlineThickness;
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
		}


		
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
    SpawnMenuButtons();
	std::cout << "spawn interval: " << EnemySpecs.SpawnInterval << "\n";
}




//--------------------------------------------


void MenuScene::SpawnMenuButtons() {
    SpawnButton(
        SinglePlayerButtonSpecs.Width, SinglePlayerButtonSpecs.Height,
        SinglePlayerButtonSpecs.X, SinglePlayerButtonSpecs.Y,
        SinglePlayerButtonSpecs.OutlineThickness, SinglePlayerButtonSpecs.OutlineColor,
        SinglePlayerButtonSpecs.FillColor,
        [this]() {
            _changeScene("play");
        }
    );
}


//--------------------------------------------


void MenuScene::SpawnButton(
    float width, float height, float x, float y,
    float outlineThickness, sf::Color outlineColor, sf::Color fillColor,
    std::function<void()> onClickFunc
) {
    auto button = EntityManager.AddEntity("Button");

    sf::Vector2f rectanglePosition{ x, y };
    button->cTransform = std::make_shared<CTransform>(rectanglePosition, sf::Vector2f(0.0f, 0.0f), 0.0f);
    button->cRectangle = std::make_shared<CRectangle>(width, height, outlineThickness, outlineColor, fillColor);

    float left = x;
    float right = x + width;
    float top = y;
    float bottom = y + height;

    button->cButton = std::make_shared<CButton>(left, right, top, bottom, onClickFunc);
}


//---------------------------------------------

//TODO change this to make something other than player to control menus
void MenuScene::SpawnPlayer()
{
	Player = EntityManager.AddEntity("Player");
	Player->cInput = std::make_shared<CInput>();
}

//--------------------------------------------


void MenuScene::sMovement()
{
	return;
}


//--------------------------------------------


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
			e->cRectangle->Rectangle.setRotation(sf::degrees(e->cTransform->Angle));
			window.draw(e->cRectangle->Rectangle);
			

		}
	}
	window.display();
}

//--------------------------------------------


void MenuScene::sSpawner()
{
	return;
}


//--------------------------------------------



void MenuScene::sUserInput()
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
        std::cout << "left click in input system \n";
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


//==============================================================



void MenuScene::sButtonClicked()
{
    auto mousex = Player->cInput->MousePos.x;
    auto mousey = Player->cInput->MousePos.y;

    if (!Player->cInput->LeftClick)
        return;  // early exit if no click

    std::cout << "detected in button system \n";
    for (auto& e : EntityManager.GetEntities()) {
        if (e->cButton != nullptr) {
            std::cout << "pointer is not null \n";
            if (mousex >= e->cButton->LeftSide && mousex <= e->cButton->RightSide &&
                mousey >= e->cButton->TopSide && mousey <= e->cButton->BottomSide)
            {
                std::cout << "click in range \n";
                if (e->cButton->onClick) {
                    std::cout << "onClick method available \n";
                    e->cButton->onClick();
                }
                else
                {
                    std::cout << "Button clicked, but onClick function is empty." << std::endl;
                }
                break; // assuming one click triggers one button only
            }
        }
    }
}




//==============================================================




//public methods
void MenuScene::update() {

		ManuelSpawnFlag = true;
		sUserInput();

		if (IsRunning) {
			GameFrameCount++;
			EntityManager.Update();
			sSpawner();
			sMovement();
			sRender();
      sButtonClicked();
		}

}


//--------------------------------------------



std::string MenuScene::nextScene() {
    return _sceneChangeNeeded ? _sceneToChangeTo : "";
}



//============================================================
//ORIGINAL COPY 

/*
#include "MenuScene.h"
#include <iostream>


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




