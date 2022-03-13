//
// Created by vladi on 3/9/2022.
//

#include "../headers/ball.hpp"
#include <cmath>

float Ball::dx[] = {1.0, -1.0, -1.0, 1.0};
float Ball::dy[] = {-1.0, -1.0, 1.0, 1.0};
float Ball::left_border = 4.0;
float Ball::right_border = 896.0;
float Ball::top_border = 4.0;
float Ball::bottom_border = 971;

Ball::Ball(){
    velocity = (float) (rand() % 3) + 1;
    radius = rand() % 61 + 40;
    life = rand() % 101; // de modificat in functie de scorul jucatorului sau timp
    dir = rand() % 2 + 2;
    alpha = rand() % 76;
    last_hit_wall = 1;
    pos.x = rand() % (900 - 2 * radius);
    pos.y = 0;
    center_pos.x = pos.x + radius;
    center_pos.y = pos.y + radius;
    circle.setRadius(radius);
    circle.setOutlineColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
    circle.setOutlineThickness(5);
    circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
    circle.setPosition(pos.x, pos.y);
}

int Ball::get_radius(){
    return this->radius;
}

int Ball::get_life(){
    return this->life;
}

sf::Vector2f Ball::get_center_pos(){
    return this->center_pos;
}

float Ball::cosine(float angle){
    return std::cos(3.14159265 * angle / 180);
}

int Ball::damage(int d){
    this->life -= d;
    return (this->life > 0);
}

void Ball::hit_wall(int wall){
    if(this->last_hit_wall == 1){
        if(wall == 2){
            this->alpha = 90 - this->alpha;
            this->dir = 3;
        }
        else if(wall == 3 && this->dir == 2)
            this->dir = 1;
        else if(wall == 3 && this->dir == 3)
            this->dir = 0;
        else if(wall == 0){
            this->alpha = 90 - this->alpha;
            this->dir = 2;
        }
    }
    else if(this->last_hit_wall == 2){
        if(wall == 3){
            this->alpha = 90 - this->alpha;
            this->dir = 0;
        }
        else if(wall == 0 && this->dir == 0)
            this->dir = 1;
        else if(wall == 0 && this->dir == 3)
            this->dir = 2;
        else if(wall == 1){
            this->alpha = 90 - this->alpha;
            this->dir = 3;
        }
    }
    else if(this->last_hit_wall == 3){
        if(wall == 0){
            this->alpha = 90 - this->alpha;
            this->dir = 1;
        }
        else if(wall == 1 && this->dir == 0)
            this->dir = 3;
        else if(wall == 1 && this->dir == 1)
            this->dir = 2;
        else if(wall == 2){
            this->alpha = 90 - this->alpha;
            this->dir = 0;
        }
    }
    else if(this->last_hit_wall == 0){
        if(wall == 1){
            this->alpha = 90 - this->alpha;
            this->dir = 2;
        }
        else if(wall == 2 && this->dir == 1)
            this->dir = 0;
        else if(wall == 2 && this->dir == 2)
            this->dir = 3;
        else if(wall == 3){
            this->alpha = 90 - this->alpha;
            this->dir = 1;
        }
    }
    this->last_hit_wall = wall;
}

void Ball::move(){
    if(this->last_hit_wall & 1){
        this->pos.x += velocity * cosine(90 - this->alpha) * dx[this->dir];
        this->pos.y += velocity * cosine(this->alpha) * dy[this->dir];
    } else {
        this->pos.x += velocity * cosine(this->alpha) * dx[this->dir];
        this->pos.y += velocity * cosine(90 - this->alpha) * dy[this->dir];
    }
    this->center_pos.x = this->pos.x + this->radius;
    this->center_pos.y = this->pos.y + this->radius;
    if(this->pos.x <= left_border)
        this->hit_wall(2);
    else if(this->pos.x + 2 * this->radius >= right_border)
        this->hit_wall(0);
    else if(this->pos.y <= top_border)
        this->hit_wall(1);
    else if(this->pos.y + 2 * this->radius >= bottom_border)
        this->hit_wall(3);

    this->circle.setPosition(this->pos);
}

std::string Ball::int_to_string(int num){
    std::string s;
    if(num == 0)
        s.push_back('0');
    for( ; num; num /= 10)
        s.push_back('0' + num % 10);
    for(int i = 0, j = s.size() - 1; i < j; i ++, j --)
        std::swap(s[i], s[j]);
    return s;
}

void Ball::generate_text(sf::RenderWindow& window){
    sf::Font font;
    font.loadFromFile("resurse/arial.ttf");
    sf::Text text(this->int_to_string(this->life), font, this->radius);
    sf::FloatRect text_rect(text.getLocalBounds());
    float x = this->pos.x + this->radius - text_rect.width / 2;
    float y = this->pos.y + this->radius - text_rect.height;
    text.setPosition((float)x, (float)y);
    window.draw(text);
}

void Ball::display(sf::RenderWindow& window){
    window.draw(this->circle);
    this->generate_text(window);
}
std::ostream& operator<<(std::ostream& os, const Ball& ball){
    os << "The ball at position " << ball.pos.x << " " << ball.pos.y << " has the speed of " << ball.velocity << " ps/sec.";
    return os;
}