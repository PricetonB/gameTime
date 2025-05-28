#ifndef FILE_STRUCTS_H
#define FILE_STRUCTS_H

//#include "Scene.h"
//#include <string>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>
//#include "EntityManager.h"



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
};

struct MultiPlayerButtonSpecsStr {
	uint16_t Width;
	uint16_t Height;
	uint16_t X;
	uint16_t Y;
	uint16_t OutlineThickness;
	sf::Color OutlineColor;
	sf::Color FillColor;
};
#endif
