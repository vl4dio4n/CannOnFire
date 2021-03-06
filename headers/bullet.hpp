//
// Created by vladi on 3/9/2022.
//

#ifndef OOP_BULLET_HPP
#define OOP_BULLET_HPP

#include "ball.hpp"
#include <SFML/Graphics.hpp>

class Bullet{
private:
    static float velocity;
    static int damage;
    static float right_border;
    float width;
    float height;
    sf::Vector2f pos;
    sf::Texture bullet_texture;
public:
    Bullet(const sf::Vector2f&, float, float);
    ~Bullet() = default;
    void display(sf::RenderWindow&);
    void move();
    bool check_collision(std::vector<Ball>&, int&);
    bool inside_circle(float, float, float, float, int);
    friend std::ostream& operator<<(std::ostream&, const Bullet&);
};

#endif //OOP_BULLET_HPP
