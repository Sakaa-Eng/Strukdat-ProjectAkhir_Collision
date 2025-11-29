#ifndef BOLA_HPP
#define BOLA_HPP

#include <SFML/Graphics.hpp>

class Bola {
private:
    sf::CircleShape bentuk;
    float vx;   
    float vy; 

public:
    Bola(float radius = 20.0f);

    void setPos(float x, float y);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};

#endif
