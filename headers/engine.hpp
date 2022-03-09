//
// Created by vladi on 3/9/2022.
//

#ifndef OOP_ENGINE_HPP
#define OOP_ENGINE_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "cannon.hpp"
#include "ball.hpp"

class Engine{
private:
    static int delay_bullets;
    static int delay_balls;
    static int window_width;
    static int window_height;
    Cannon tank;
    std::vector<Ball> balls;
    sf::Clock clock;
    sf::Texture background_texture;

public:
    Engine();
    std::string int_to_string(int);
    void display_text(sf::RenderWindow&, std::string&, float, float);
    void run();
};

#endif //OOP_ENGINE_HPP
