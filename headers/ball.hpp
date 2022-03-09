//
// Created by vladi on 3/9/2022.
//

#ifndef OOP_BALL_HPP
#define OOP_BALL_HPP

#include <SFML/Graphics.hpp>

class Ball{
private:
    static float dx[4];
    static float dy[4];
    static float left_border;
    static float right_border;
    static float top_border;
    static float bottom_border;
    float velocity;
    int radius;
    int life;
    int dir;
    int alpha;
    int last_hit_wall;
    sf::Vector2f pos;
    sf::Vector2f center_pos;
    sf::CircleShape circle;
public:
    Ball();
    int get_radius();
    int get_life();
    float cosine(float);
    void hit_wall(int);
    void move();
    int damage(int);
    sf::Vector2f get_center_pos();
    std::string int_to_string(int);
    void generate_text(sf::RenderWindow&);
    void display(sf::RenderWindow&);
};

#endif //OOP_BALL_HPP
