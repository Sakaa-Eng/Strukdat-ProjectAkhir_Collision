#include <SFML/Graphics.hpp>
#include "Bola.hpp"

int main() {
    const int Lebar = 1200;
    const int Tinggi = 800;

    sf::RenderWindow window(sf::VideoMode(Lebar, Tinggi), "Banyak Bola & Collision");
    window.setFramerateLimit(60);


    Bola bola1(100, 200, 30, sf::Vector2f(180, 120));
    Bola bola2(500, 300, 30, sf::Vector2f(-150, -100));

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        bola1.update(dt, window);
        bola2.update(dt, window);

        window.clear();
        window.draw(bola1.shape);
        window.draw(bola2.shape);
        window.display();
    }

    return 0;
}
