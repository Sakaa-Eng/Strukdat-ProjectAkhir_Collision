#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string> 

struct Bola {
    sf::CircleShape shape;
    sf::Vector2f velocity; // Kecepatan (x, y)

    Bola(float x, float y, float radius, sf::Vector2f vel) {
        shape.setPosition(x, y);
        shape.setRadius(radius);
        shape.setOrigin(radius, radius); 
        velocity = vel;
    }

    void update(float dt, const sf::RenderWindow& window) {
        shape.move(velocity * dt);

        sf::Vector2f pos = shape.getPosition();
        float r = shape.getRadius();
        float w = (float)window.getSize().x;
        float h = (float)window.getSize().y;

        // Cek kiri kanan
        if (pos.x - r < 0) {
            velocity.x = std::abs(velocity.x);
            shape.setPosition(r, pos.y);
        } else if (pos.x + r > w) {
            velocity.x = -std::abs(velocity.x);
            shape.setPosition(w - r, pos.y);
        }

        // Cek atas bawah
        if (pos.y - r < 0) {
            velocity.y = std::abs(velocity.y);
            shape.setPosition(pos.x, r);
        } else if (pos.y + r > h) {
            velocity.y = -std::abs(velocity.y);
            shape.setPosition(pos.x, h - r);
        }
    }
};


float randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
}

sf::Color getRandomColor();

void addBallsAt(std::vector<Bola> &bolaList, const std::vector<float> &ukuranBola, float x, float y, int count) {
    for(int i = 0; i < count; ++i) {
        float r = ukuranBola[rand() % ukuranBola.size()];
        float vx = randomFloat(-200, 200);
        float vy = randomFloat(-200, 200);
        if(std::abs(vx) < 30) vx = 30;
        if(std::abs(vy) < 30) vy = 30;
        Bola b(x, y, r, {vx, vy});
        b.shape.setFillColor(getRandomColor());
        bolaList.push_back(b);
    }
}

void removeBallsAt(std::vector<Bola> &bolaList, float x, float y, int count) {
    for(int c = 0; c < count && !bolaList.empty(); ++c) {
        bool removed = false;
        for(auto it = bolaList.begin(); it != bolaList.end(); ++it) {
            float bx = it->shape.getPosition().x;
            float by = it->shape.getPosition().y;
            float r = it->shape.getRadius();
            float dx = bx - x;
            float dy = by - y;
            if(std::sqrt(dx*dx + dy*dy) <= r) {
                bolaList.erase(it);
                removed = true;
                break;
            }
        }
        if(!removed) bolaList.pop_back();
    }
}

sf::Color getRandomColor() {
    static std::vector<sf::Color> colors = {
        sf::Color(128, 0, 128), // Ungu
        sf::Color::Magenta,     // Magenta
        sf::Color(139, 69, 19), // Coklat
        sf::Color::Cyan         // Cyan
    };
    return colors[rand() % colors.size()];
}

//Colossion
void cekCollision(Bola &a, Bola &b) {
    float ax = a.shape.getPosition().x;
    float ay = a.shape.getPosition().y;
    float bx = b.shape.getPosition().x;
    float by = b.shape.getPosition().y;

    float dx = bx - ax;
    float dy = by - ay;
    float jarak = std::sqrt(dx * dx + dy * dy);
    float minDist = a.shape.getRadius() + b.shape.getRadius();

    // Jarak kurang dari jari-jari yang seharusnya berarti tabrakan
    if (jarak < minDist) {
        if (jarak == 0.0f) jarak = 0.01f; 

        float nx = dx / jarak;
        float ny = dy / jarak;

        float overlap = minDist - jarak;
        float moveX = nx * overlap * 0.5f;
        float moveY = ny * overlap * 0.5f;
        a.shape.move(-moveX, -moveY);
        b.shape.move(moveX, moveY);

        float rvx = b.velocity.x - a.velocity.x;
        float rvy = b.velocity.y - a.velocity.y;
        float velNormal = rvx * nx + rvy * ny;

        if (velNormal > 0) return; 

        float impulse = -(1.0f + 1.0f) * velNormal / 2.0f; 
        
        a.velocity.x -= impulse * nx;
        a.velocity.y -= impulse * ny;
        b.velocity.x += impulse * nx;
        b.velocity.y += impulse * ny;
    }
}

struct Quadtree {
    static const int MAX_OBJECTS = 4; 
    static const int MAX_LEVELS = 6; 

    int level;
    sf::FloatRect bounds; 
    std::vector<Bola*> objects; 
    Quadtree* nodes[4]; 

    Quadtree(int pLevel, sf::FloatRect pBounds) : level(pLevel), bounds(pBounds) {
        for(int i=0; i<4; i++) nodes[i] = nullptr;
    }

    ~Quadtree() { clear(); }

    void clear() {
        objects.clear();
        for(int i=0; i<4; i++) {
            if(nodes[i]) {
                delete nodes[i];
                nodes[i] = nullptr;
            }
        }
    }

    void split() {
        float subW = bounds.width / 2.f;
        float subH = bounds.height / 2.f;
        float x = bounds.left;
        float y = bounds.top;

        nodes[0] = new Quadtree(level+1, sf::FloatRect(x, y, subW, subH));
        nodes[1] = new Quadtree(level+1, sf::FloatRect(x + subW, y, subW, subH));
        nodes[2] = new Quadtree(level+1, sf::FloatRect(x, y + subH, subW, subH));
        nodes[3] = new Quadtree(level+1, sf::FloatRect(x + subW, y + subH, subW, subH));
    }

    int getIndex(Bola* b) {
        float x = b->shape.getPosition().x;
        float y = b->shape.getPosition().y;
        float r = b->shape.getRadius();

        float verticalMid = bounds.left + (bounds.width / 2.f);
        float horizontalMid = bounds.top + (bounds.height / 2.f);

        bool topQuadrant = (y + r < horizontalMid);
        bool bottomQuadrant = (y - r > horizontalMid);
        bool leftQuadrant = (x + r < verticalMid);
        bool rightQuadrant = (x - r > verticalMid);

        if(leftQuadrant) {
            if(topQuadrant) return 0;
            if(bottomQuadrant) return 2;
        }
        else if(rightQuadrant) {
            if(topQuadrant) return 1;
            if(bottomQuadrant) return 3;
        }
        return -1;
    }

    void insert(Bola* b) {
        if(nodes[0]) {
            int index = getIndex(b);
            if(index != -1) {
                nodes[index]->insert(b);
                return;
            }
        }
        objects.push_back(b);

        if(objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
            if(!nodes[0]) split();
            int i = 0;
            while(i < objects.size()) {
                int index = getIndex(objects[i]);
                if(index != -1) {
                    nodes[index]->insert(objects[i]);
                    objects.erase(objects.begin() + i);
                } else {
                    i++;
                }
            }
        }
    }

    void retrieve(std::vector<Bola*>& returnObjects, Bola* b) {
        int index = getIndex(b);
        if(index != -1 && nodes[0]) {
            nodes[index]->retrieve(returnObjects, b);
        } else if (nodes[0]) {
            for(int i=0; i<4; i++) nodes[i]->retrieve(returnObjects, b);
        }
        returnObjects.insert(returnObjects.end(), objects.begin(), objects.end());
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Collision: Quadtree vs BruteForce");
    window.setFramerateLimit(144); 

    srand((unsigned int)time(nullptr));

    std::vector<Bola> bolaList;
    std::vector<float> ukuranBola = {20.f, 20.f, 20.f, 20.f};

    int jumlahBolaAwal = 500; 

    for(int i = 0; i < jumlahBolaAwal; i++) {
        float r = ukuranBola[rand() % ukuranBola.size()];
        float x = randomFloat(r, 1280 - r); 
        float y = randomFloat(r, 720 - r);
        
        float vx = randomFloat(-200, 200); 
        float vy = randomFloat(-200, 200);
        
        if(std::abs(vx) < 30) vx = 30;
        if(std::abs(vy) < 30) vy = 30;
        
        Bola b(x, y, r, {vx, vy});
        b.shape.setFillColor(getRandomColor());
        bolaList.push_back(b);
    }

    bool useQuadtree = true; 
    sf::Clock clock;
    
    sf::Font font;
    sf::Text textInfo;
    if(font.loadFromFile("Baxoe.ttf")) {
        textInfo.setFont(font);
        textInfo.setCharacterSize(20);
        textInfo.setFillColor(sf::Color::White);
        textInfo.setPosition(10, 10);
    }

    std::vector<Bola*> candidates; 

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) window.close();
            
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                useQuadtree = !useQuadtree;
            }

            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                float x = event.mouseButton.x;
                float y = event.mouseButton.y;
                addBallsAt(bolaList, ukuranBola, x, y, 1);
            }

            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::A) {
                    sf::Vector2i mp = sf::Mouse::getPosition(window);
                    addBallsAt(bolaList, ukuranBola, static_cast<float>(mp.x), static_cast<float>(mp.y), 50);
                } else if(event.key.code == sf::Keyboard::D) {
                    sf::Vector2i mp = sf::Mouse::getPosition(window);
                    removeBallsAt(bolaList, static_cast<float>(mp.x), static_cast<float>(mp.y), 50);
                }
            }
        }

        float dt = clock.restart().asSeconds();
        float fps = 1.0f / dt;

    
        for(auto& b : bolaList) b.update(dt, window);

        
        if(useQuadtree) {
            // CARA 1: QUADTREE 
            Quadtree qt(0, sf::FloatRect(0, 0, 1280, 720));
            for(auto& b : bolaList) qt.insert(&b);

            candidates.reserve(bolaList.size());
            for(auto& b : bolaList) {
                candidates.clear();
                qt.retrieve(candidates, &b); 
                for(auto* other : candidates) {
                    if(&b != other) cekCollision(b, *other);
                }
            }
        } else {
            // CARA 2: BRUTE FORCE (Cek Semua)
            for(size_t i = 0; i < bolaList.size(); i++) {
                for(size_t j = i + 1; j < bolaList.size(); j++) {
                    cekCollision(bolaList[i], bolaList[j]);
                }
            }
        }

        if(font.getInfo().family != "") {
            std::string mode = useQuadtree ? "Quadtree (ON)" : "Brute Force (OFF)";
            textInfo.setString("Mode: " + mode + " [SPASI]\nFPS: " + std::to_string((int)fps) + "\nBola: " + std::to_string(bolaList.size()) + "\nTouch: +50\nRight click: -1");
        }

        window.clear(sf::Color::Black);
        for(auto& b : bolaList) window.draw(b.shape);
        window.draw(textInfo);
        window.display();
    }

    return 0;
}