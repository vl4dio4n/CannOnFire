//
// Created by vladi on 3/11/2022.
//

#include "../headers/button.hpp"

Button::Button(int width, int height, float outline_thickness, sf::Vector2f& pos, const std::string& text, const sf::Color& fill_color, const sf::Color& outline_color, const sf::Color& text_color):
    width{width}, height{height}, outline_thickness{outline_thickness}, text{text}, pos{pos}, fill_color{fill_color}, outline_color{outline_color}, text_color{text_color}{}

void Button::display(sf::RenderWindow &window) {
    this->rect.setPosition(this->pos);
    this->rect.setSize(sf::Vector2f((float)this->width, (float)this->height));
    this->rect.setFillColor(this->fill_color);
    this->rect.setOutlineColor(this->outline_color);
    this->rect.setOutlineThickness(this->outline_thickness);
    window.draw(this->rect);
    display_text(window);
}
void Button::display_text(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("resurse/arial.ttf");
    sf::Text text_obj(this->text, font, this->height / 2);
    sf::FloatRect text_rect(text_obj.getLocalBounds());
    float x = this->pos.x + this->width / 2 - text_rect.width / 2;
    float y = this->pos.y + this->height / 2 - text_rect.height;
    text_obj.setPosition((float)x, (float)y);
    text_obj.setFillColor(this->text_color);
    window.draw(text_obj);
}

void Button::set_fill_color(const sf::Color& color) {
    fill_color = color;
}

void Button::set_outline_color(const sf::Color& color) {
    outline_color = color;
}

void Button::set_text_color(const sf::Color& color) {
    text_color = color;
}

bool Button::check_hover(sf::Vector2f mouse_pos) {
    return mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + width && mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + height;
}

std::string Button::get_text(){
    return text;
}