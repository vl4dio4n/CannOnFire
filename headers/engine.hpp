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
#include "button.hpp"

class Engine{
private:
    static int delay_bullets;
    static int delay_balls;
    static float window_width;
    static float window_height;
    Cannon tank;
    std::vector<Ball> balls;
    std::vector<std::pair<Button, std::vector<std::string>>> buttons;
    sf::Clock clock;
    sf::Texture background_texture;

public:
    Engine();
    ~Engine();
    std::string int_to_string(int);
    void display_text(sf::RenderWindow&, std::string&, float, float);
    void run();
    void reset_game();
    friend std::ostream& operator<<(std::ostream&, const Engine&);
};

#endif //OOP_ENGINE_HPP
