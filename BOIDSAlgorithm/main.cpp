#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <cstdlib> 
#include <vector>


struct Boid : public sf::CircleShape
{
	float radius = 2;
	sf::Vector3i color = { 255,255,255 };
	sf::Vector2f Velocity;

	float protectedRange = 10.0;
	float centeringfactor = 0.0005;
	float matchingfactor = 0.05;
	float minspeed = 1.0;

	float turnfactor = 0.2;
	float visualRange = 40;
	float avoidfactor = 0.05;
	float maxspeed = 6.0;

	Boid(const sf::Vector2f& initial_pos, const sf::Vector2f& initial_vel)
	{
		this->Velocity = initial_vel;

		this->setPosition(initial_pos);
		this->setFillColor(sf::Color(color.x, color.y, color.z));
		this->setRadius(radius);
	}
};


void checkMargin(sf::RenderWindow &win, Boid& boid)
{
	float margin = 100.0;
	sf::Vector2f pos = boid.getPosition();

	if (pos.x < margin)
		boid.Velocity.x += boid.turnfactor;
	if (pos.x > win.getSize().x - margin)
		boid.Velocity.x -= boid.turnfactor;
	
	if (pos.y < margin)
		boid.Velocity.y += boid.turnfactor;
	if (pos.y > win.getSize().y - margin)
		boid.Velocity.y -= boid.turnfactor;
}

void updateBoidVel(std::vector<Boid>& boids, Boid& boid, sf::RenderWindow& window)
{
	sf::Vector2f pos_avg;
	sf::Vector2f vel_avg;
	sf::Vector2f close;
	sf::Vector2f dist;
	float neighboring = 0.0;
	float squaredDist = 0.0;

	for (auto& b : boids)
	{
		if (&b == &boid)
			continue;

		dist.x = boid.getPosition().x - b.getPosition().x;
		dist.y = boid.getPosition().y - b.getPosition().y;

		squaredDist = dist.x * dist.x + dist.y * dist.y;

		if (squaredDist < (boid.protectedRange * boid.protectedRange) )
		{
			close.x += boid.getPosition().x - b.getPosition().x;
			close.y += boid.getPosition().y - b.getPosition().y;
		}
		else if (squaredDist < (boid.visualRange * boid.visualRange))
		{
			pos_avg.x += b.getPosition().x;
			pos_avg.y += b.getPosition().y;
			vel_avg.x += b.Velocity.x;
			vel_avg.y += b.Velocity.y;

			neighboring++;
		}
	}

	if (neighboring > 0)
	{
		close /= neighboring;
		boid.Velocity += close * boid.avoidfactor;

		pos_avg.x = pos_avg.x / neighboring;
		pos_avg.y = pos_avg.y / neighboring;
		vel_avg.x = vel_avg.x / neighboring;
		vel_avg.y = vel_avg.y / neighboring;

		boid.Velocity.x += (pos_avg.x - boid.getPosition().x) * boid.centeringfactor +
			(vel_avg.x - boid.Velocity.x) * boid.matchingfactor;

		boid.Velocity.y += (pos_avg.y - boid.getPosition().y) * boid.centeringfactor +
			(vel_avg.y - boid.Velocity.y) * boid.matchingfactor;

	}
	float speed = sqrt(boid.Velocity.x * boid.Velocity.x + boid.Velocity.y * boid.Velocity.y);

	if (speed < boid.minspeed)
	{
		boid.Velocity.x = (boid.Velocity.x / speed) * boid.minspeed;
		boid.Velocity.y = (boid.Velocity.y / speed) * boid.minspeed;
	}
	if (speed > boid.maxspeed)
	{
		boid.Velocity.x = (boid.Velocity.x / speed) * boid.maxspeed;
		boid.Velocity.y = (boid.Velocity.y / speed) * boid.maxspeed;
	}

	// Update boid's position
	boid.setPosition(boid.getPosition().x + boid.Velocity.x, boid.getPosition().y + boid.Velocity.y);


	checkMargin(window, boid);
	boid.move(boid.Velocity.x, boid.Velocity.y);
	window.draw(boid);
}


int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "BOIDS Algorithm");
	window.setFramerateLimit(60);


	// Generate BOIDS here
	std::vector<Boid> boids;

	float circleRad = 200.0f;
	sf::Vector2f center = { window.getSize().x / 2.0f, window.getSize().y / 2.0f };

	// All the boids are placed in a circle of radius circleRad
	// with center at center of the window.

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> angleDist(0, 2 * 3.14);
	std::uniform_real_distribution<float> radiusDist(0, circleRad);

	for (int i = 0; i < 2000; ++i)
	{
		float angle = angleDist(gen);
		float radius = radiusDist(gen);

		float x = center.x + radius * std::cos(angle);
		float y = center.y + radius * std::sin(angle);

		sf::Vector2f pos(x,y);
		sf::Vector2f initial_vel(0, 0); // Initialize with appropriate velocity
		boids.push_back(Boid(pos, initial_vel));
	}

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (auto& b : boids)
		{
			updateBoidVel(boids, b, window);
		}
		window.display();
	}
	return 0;
}
