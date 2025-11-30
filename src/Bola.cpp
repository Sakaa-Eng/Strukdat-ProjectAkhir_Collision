#include "Bola.hpp"

Bola::Bola(float x, float y, float radius, sf::Vector2f vel) {
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, y);
    velocity = vel;
}

void Bola::update(float dt, sf::RenderWindow &window) {
    sf::Vector2f pos = shape.getPosition();
    pos += velocity * dt;

    float r = shape.getRadius();
    sf::Vector2u win = window.getSize();

    if (pos.x < 0 || pos.x + 2*r > win.x) {
        velocity.x *= -1;
    }

    if (pos.y < 0 || pos.y + 2*r > win.y) {
        velocity.y *= -1;
    }

    shape.setPosition(pos);
}
