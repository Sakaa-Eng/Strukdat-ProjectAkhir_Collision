#include "Bola.hpp"

Bola::Bola(float radius) {
    bentuk.setRadius(radius);
    bentuk.setFillColor(sf::Color::White);
    
    vx = 3.5f;
    vy = 2.5f;

    bentuk.setPosition(100, 100);
}

void Bola::setPos(float x, float y) {
    bentuk.setPosition(x, y);
}

void Bola::update(sf::RenderWindow& window) {
    sf::Vector2f pos = bentuk.getPosition();
    float diameter = bentuk.getRadius() * 2;

    if (pos.x <= 0 || pos.x + diameter >= window.getSize().x) {
        vx = -vx;
    }

    if (pos.y <= 0 || pos.y + diameter >= window.getSize().y) {
        vy = -vy;
    }

    bentuk.move(vx, vy);
}

void Bola::draw(sf::RenderWindow& window) {
    window.draw(bentuk);
}
