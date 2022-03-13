//
// Created by vladi on 3/11/2022.
//

#ifndef OOP_BUTTON_HPP
#define OOP_BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button{
private:
    int width;
    int height;
    float outline_thickness;
    std::string text;
    sf::Vector2f pos;
    sf::RectangleShape rect;
    sf::Color fill_color;
    sf::Color outline_color;
    sf::Color text_color;
public:
    Button(int, int, float, sf::Vector2f&, std::string, const sf::Color&, const sf::Color&, const sf::Color&);
    void display(sf::RenderWindow&);
    void display_text(sf::RenderWindow&);
    bool check_hover(sf::Vector2f);
    void set_fill_color(sf::Color&);
    void set_outline_color(sf::Color&);
    void set_text_color(sf::Color&);
    std::string get_text();
};

#endif //OOP_BUTTON_HPP
