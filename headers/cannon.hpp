//
// Created by vladi on 3/9/2022.
//

#ifndef OOP_CANNON_HPP
#define OOP_CANNON_HPP

#include <vector>
#include "ball.hpp"
#include "bullet.hpp"

class Cannon{
private:
    static float velocity;
    static float left_border;
    static float right_border;
    static float window_width;
    static float window_height;
    static float offset;
    int score;
    float width;
    float height;
    std::vector <Bullet> bullets;
    sf::Vector2f pos;
    sf::Texture tank_texture;
public:
    Cannon();
    void display(sf::RenderWindow&);
    void move(const std::string&);
    void shoot();
    void update(std::vector<Ball>&, int&);
    bool check_hit(std::vector <Ball>&);
};

#endif //OOP_CANNON_HPP
