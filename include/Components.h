#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>



class CTransform {
public:
	sf::Vector2f Position = {0.0f, 0.0f };
	sf::Vector2f Velocity = {0.0f, 0.0f };
	float Angle = 0.0f;

	CTransform(const sf::Vector2f & position, const sf::Vector2f & velocity, const float & angle)
		: Position(position), Velocity(velocity), Angle(angle) {}
};

//=============================================================

class CShape {
public:
	sf::CircleShape Shape;

	CShape(const float  radius, const size_t pointCount, const sf::Color& fillColor, const sf::Color& outlineColor, const float thickness) {
		Shape = sf::CircleShape(radius, pointCount);
		Shape.setFillColor(fillColor);
		Shape.setOutlineColor(outlineColor);
		Shape.setOutlineThickness(thickness);
		//Shape.setOrigin(sf::Vector2f(radius, radius));  // Correct way to set the origin with a Vector2f

	}
};

//=============================================================

//TODO update whatever draws Cshape to also draw Crectangele

class CRectangle {
public:
    sf::RectangleShape Rectangle;

    CRectangle(float width, float height, float thickness, const sf::Color& outlineColor, const sf::Color& fillColor ) {
        Rectangle.setSize(sf::Vector2f(width, height));
        Rectangle.setFillColor(fillColor);
        Rectangle.setOutlineColor(outlineColor);
        Rectangle.setOutlineThickness(thickness);
        //Rectangle.setOrigin(sf::Vector2f(width,height));  // Center origin
    }
};



//=============================================================


class CText {
public:
  sf::Text Text;

  CText(const sf::Font& font, const std::string& textString, int fontSize)
  :Text(font)
{
    Text.setCharacterSize(fontSize);
    Text.setString(textString);
    Text.setFillColor(sf::Color(255,255,255));

  }




};

//=============================================================


class CScore {
public:
	int Score = 0;

	CScore(const int score)
		:Score(score) {}
};

//=============================================================


class CCollision {
public:
	float Radius = 0;

	CCollision(const float radius)
		:Radius(radius) {}
};

//=============================================================


class CLifeSpan {
public:
	int TotalLife;
	int RemainingLife;

	CLifeSpan(const int life)
		:TotalLife(life), RemainingLife(life) {}
};

//=============================================================


class CSpecialShoot {
public:
	int BulletAmount;
	int Cooldown;
	int RemainingCooldown;
	CSpecialShoot(int bulletAmount, int cooldown)
		:BulletAmount(bulletAmount), Cooldown(cooldown), RemainingCooldown(0){}
};

//=============================================================

class CShoot {
public:
	int Cooldown;
	int RemainingCooldown;
	CShoot(int cooldown)
		:Cooldown(cooldown), RemainingCooldown(0){}
};

//=============================================================



//TODO shoot and special shoot needs to be changed to left click and right click. 
//it needs to then be modified in every scene that uses this input system. 
//maybe make a shoot component like the special shoot component above:
class CInput {
public:
	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool LeftClick;
	bool RightClick;
	sf::Vector2f MousePos;

	CInput()
		:Up(false), Down(false) , Left(false) , Right(false), LeftClick(false), RightClick(false){
		MousePos = sf::Vector2f(0, 0);
	}
};

//=============================================================


class CButton {
public:
    std::function<void()> onClick;
    bool ButtonClicked = false; //TODO DELETE THIS. WE JUST CALL ONCLICK INSTEAD OF MAKING THIS TRUE
    float LeftSide, RightSide, TopSide, BottomSide;

    CButton(float left, float right, float top, float bottom, std::function<void()> onClickFunc)
        : LeftSide(left), RightSide(right), TopSide(top), BottomSide(bottom), onClick(onClickFunc) {}
};







