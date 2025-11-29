#include <SFML/Graphics.hpp>
#include "Bola.hpp"

int main() {
    const int Lebar = 600;
    const int Tinggi = 400;

    sf::RenderWindow window(sf::VideoMode(Lebar, Tinggi), "Bola mantul kanan kiri atas bawah");
    window.setFramerateLimit(60);

    Bola bola(25);
    bola.setPos(Lebar/2, Tinggi/2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        bola.update(window);

        window.clear();
        bola.draw(window);
        window.display();
    }

    return 0;
}
