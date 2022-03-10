//
// Created by vladi on 3/9/2022.
//

#include "../headers/cannon.hpp"

float Cannon::velocity = 3.0;
float Cannon::left_border = 0.0;
float Cannon::right_border = 900.0;
float Cannon::window_width = 900.0;
float Cannon::window_height = 1050.0;
float Cannon::offset = 75.0;

void Cannon::shoot(){
    this->bullets.push_back(Bullet(this->pos, this->width, this->height));
}

void Cannon::update(std::vector<Ball>& balls, int& scr){
    for(auto& bullet: this->bullets)
        bullet.move();
    for(int i = this->bullets.size() - 1; i >= 0; i --)
        if(this->bullets[i].check_collision(balls, scr))
            this->bullets.erase(this->bullets.begin() + i);
}

void Cannon::move(const std::string& dir){
    if(dir == "right")
        this->pos.x = std::min(this->pos.x + velocity, right_border - this->width);
    else
        this->pos.x = std::max(this->pos.x - velocity, left_border);
}

// bool Cannon::check_hit(std::vector <Ball>& balls){
//     for(auto& ball: balls){
//         sf::Vector2f ball_center(ball.get_center_pos());
//         int radius = ball.get_radius();
//         float x1 = this->pos.x;
//         float x2 = this->pos.x + this->width;

//         if(ball_center.y + radius >= this->pos.y + 30){
//             if((ball_center.x - radius <= x1 && x1 <= ball_center.x + radius) ||
//                (ball_center.x - radius <= x2 && x2 <= ball_center.x + radius) ||
//                (x1 <= ball_center.x && ball_center.x <= x2))
//                 return 1;
//         }
//     }
//     return 0;
// }

Cannon::Cannon(){
    score = 0;
    tank_texture.loadFromFile("resurse/tank.png");
    sf::Sprite tank;
    tank.setTexture(tank_texture);
    sf::FloatRect tank_rect(tank.getLocalBounds());
    width = tank_rect.width;
    height = tank_rect.height;
    pos.x = window_width / 2 - width / 2;
    pos.y = window_height - offset - height;
}

void Cannon::display(sf::RenderWindow& window){
    for(auto& bullet: this->bullets)
        bullet.display(window);
    sf::Sprite tank;
    tank.setTexture(this->tank_texture);
    tank.setPosition(this->pos);
    window.draw(tank);
}
