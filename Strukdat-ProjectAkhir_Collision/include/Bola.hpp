#ifndef BOLA_HPP
#define BOLA_HPP

#include <SFML/Graphics.hpp>

class Bola {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Bola(float x, float y, float radius, sf::Vector2f velocity);
    void update(float dt, const sf::RenderWindow &window);
};

#endif
