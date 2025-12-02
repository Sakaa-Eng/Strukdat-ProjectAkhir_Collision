#pragma once
#include <SFML/Graphics.hpp>

class Bola {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Bola(float x, float y, float radius, sf::Vector2f vel);

    void update(float dt, sf::RenderWindow &window);
};
