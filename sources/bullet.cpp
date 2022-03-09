//
// Created by vladi on 3/9/2022.
//

#include "../headers/bullet.hpp"

float Bullet::velocity = 6.0;
int Bullet::damage = 2;
float Bullet::left_border = 0.0;
float Bullet::right_border = 900.0;

void Bullet::move(){
    this->pos.y -= velocity;
}

bool Bullet::inside_circle(float bullet_x , float bullet_y, float center_x, float center_y, int radius){
    if((bullet_x - center_x) * (bullet_x - center_x) + (bullet_y - center_y) * (bullet_y - center_y) <= radius * radius)
        return 1;
    return 0;
}

bool Bullet::check_collision(std::vector<Ball>& balls, int& score){
    if(this->pos.y + this->height <= 0)
        return 1;
    for(int i = balls.size() - 1; i >= 0; i --){
        sf::Vector2f ball_center(balls[i].get_center_pos());
        if(this->inside_circle(this->pos.x, this->pos.y, ball_center.x, ball_center.y, balls[i].get_radius())){
            score += std::min(balls[i].get_life(), this->damage);
            bool alive = balls[i].damage(this->damage);
            if(!alive)
                balls.erase(balls.begin() + i);
            return 1;
        }
    }
    return 0;
}

Bullet::Bullet(const sf::Vector2f& tank_pos, float tank_width, float tank_height){
    bullet_texture.loadFromFile("resurse/bullet.png");
    sf::Sprite bullet_sprite;
    bullet_sprite.setTexture(bullet_texture);
    sf::FloatRect bullet_rect(bullet_sprite.getLocalBounds());
    width = bullet_rect.width;
    height = bullet_rect.height;
    pos.x = tank_pos.x + tank_width / 2 - width / 2;
    pos.y = tank_pos.y + tank_height - height;
}

void Bullet::display(sf::RenderWindow& window){
    sf::Sprite bullet_sprite;
    bullet_sprite.setTexture(this->bullet_texture);
    bullet_sprite.setPosition(this->pos);
    window.draw(bullet_sprite);
}
