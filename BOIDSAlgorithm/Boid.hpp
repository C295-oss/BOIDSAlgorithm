#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Boid
{
private:
	sf::CircleShape boid;

	sf::Vector2f pos = { 0,0 };
	sf::Vector2f velocity = { 0,0 };
	sf::Vector2f close_d = { 0,0 };

public:
	Boid(float rad, sf::Vector3i rgbVals, sf::Vector2f pos)
	{
		boid.setRadius(rad);
		boid.setFillColor(sf::Color(rgbVals.x, rgbVals.y, rgbVals.z));
		boid.move(pos);
	}

	~Boid()
	{
	}
};
/*
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <vector>


class Boid
{
private:
	sf::CircleShape boid;

	sf::Vector2f pos = { 0,0 };
	sf::Vector2f velocity = { 0,0 };
	sf::Vector2f close_d = { 0,0 };

	int visualRange = 80;
	int protectedRange = 8;
	int radius = 0;
	float minSpeed = 0.5;
	float maxSpeed = 1.5;

public:
	Boid(float rad, sf::Vector3i rgbVals, sf::Vector2f pos)
	{
		boid.setRadius(rad);
		boid.setFillColor(sf::Color(rgbVals.x, rgbVals.y, rgbVals.z));
		boid.move(pos);
	}

	~Boid()
	{
	}

	sf::Color getRGB() const { return boid.getFillColor(); }
	int getProtectedRange() const { return this->protectedRange; }
	int getVisualRange() const { return this->visualRange; }
	float getMaxSpeed() const { return this->maxSpeed; }
	float getMinSpeed() const { return this->minSpeed; }

	sf::Vector2f getVelocity() const { return this->velocity; }
	sf::Vector2f getPos() const { return pos; }

	void setVelocityX(float x) { velocity.x = x; }
	void setVelocityY(float y) { velocity.y = y; }
	void setPos(float x, float y)
	{
		this->pos.x = x;
		this->pos.y = y;
	}

	void render(sf::RenderWindow& win)
	{
		boid.move(pos);
		win.draw(boid);
	}
};
*/