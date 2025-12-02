#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Bola.hpp"

void cekCollision(Bola &a, Bola &b) {
    float ax = a.shape.getPosition().x;
    float ay = a.shape.getPosition().y;
    float bx = b.shape.getPosition().x;
    float by = b.shape.getPosition().y;

    float dx = bx - ax;
    float dy = by - ay;
    float jarak = std::sqrt(dx*dx + dy*dy);

    float ra = a.shape.getRadius();
    float rb = b.shape.getRadius();

    if (jarak < ra + rb) {
        std::swap(a.velocity, b.velocity);

        float overlap = (ra + rb) - jarak;
        float nx = dx / jarak;
        float ny = dy / jarak;

        a.shape.move(-nx * overlap/2, -ny * overlap/2);
        b.shape.move( nx * overlap/2,  ny * overlap/2);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 600), "Collision");
    window.setFramerateLimit(60);

    std::vector<Bola> bolaList;

    for (int i = 0; i < 10; i++) {
        float x = 50 + rand() % 800;
        float y = 50 + rand() % 500;
        float r = 20;

        sf::Vector2f vel(
            (rand() % 200) - 100,
            (rand() % 200) - 100
        );

        bolaList.push_back(Bola(x, y, r, vel));
    }

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        for (auto &b : bolaList) {
            b.update(dt, window);
        }

        for (int i = 0; i < (int)bolaList.size(); i++) {
            for (int j = i + 1; j < (int)bolaList.size(); j++) {
                cekCollision(bolaList[i], bolaList[j]);
            }
        }

        window.clear();
        for (auto &b : bolaList)
            window.draw(b.shape);
        window.display();
    }

    return 0;
}
