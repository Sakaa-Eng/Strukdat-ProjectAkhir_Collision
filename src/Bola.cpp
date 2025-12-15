#include "Bola.hpp"

Bola::Bola(float x, float y, float radius, sf::Vector2f vel) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    velocity = vel;
}

void Bola::update(float dt, const sf::RenderWindow& window) {
    // Gerakkan berdasarkan velocity * dt
    shape.move(velocity * dt);

    float x = shape.getPosition().x;
    float y = shape.getPosition().y;
    float r = shape.getRadius();
    float w = (float)window.getSize().x;
    float h = (float)window.getSize().y;

    // Bounce kiri/kanan (set position ke batas agar tidak terjebak)
    if (x - r < 0.0f) {
        shape.setPosition(r, y);
        velocity.x = std::abs(velocity.x);
    } else if (x + r > w) {
        shape.setPosition(w - r, y);
        velocity.x = -std::abs(velocity.x);
    }

    // Bounce atas/bawah
    if (y - r < 0.0f) {
        shape.setPosition(x, r);
        velocity.y = std::abs(velocity.y);
    } else if (y + r > h) {
        shape.setPosition(x, h - r);
        velocity.y = -std::abs(velocity.y);
    }
}
