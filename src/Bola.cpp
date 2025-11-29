#include "Bola.hpp"

Bola::Bola(float radius) {
    bentuk.setRadius(radius);
    bentuk.setFillColor(sf::Color::White);

    kecepatanY = 4.0f;            
    bentuk.setPosition(100, 100);
}

void Bola::setPos(float x, float y) {
    bentuk.setPosition(x, y);
}

void Bola::update(sf::RenderWindow& window) {
    sf::Vector2f pos = bentuk.getPosition();
    float diameter = bentuk.getRadius() * 2;

    if (pos.y <= 0 || pos.y + diameter >= window.getSize().y) {
        kecepatanY = -kecepatanY;   
    }

    bentuk.move(0, kecepatanY);   
}

void Bola::draw(sf::RenderWindow& window) {
    window.draw(bentuk);
}
