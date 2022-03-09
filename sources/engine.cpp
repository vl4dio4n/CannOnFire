//
// Created by vladi on 3/9/2022.
//

#include "../headers/engine.hpp"

int Engine::delay_bullets = 100;
int Engine::delay_balls = 20000;
int Engine::window_width = 900;
int Engine::window_height = 1050.0;

Engine::Engine(){
    balls.push_back(Ball());
    background_texture.loadFromFile("resurse/background.jpg");
}

std::string Engine::int_to_string(int num){
    std::string s;
    if(num == 0)
        s.push_back('0');
    for( ; num; num /= 10)
        s.push_back('0' + num % 10);
    for(int i = 0, j = s.size() - 1; i < j; i ++, j --)
        std::swap(s[i], s[j]);
    return s;
}

void Engine::display_text(sf::RenderWindow& window, std::string& s, float x, float y){
    sf::Font font;
    font.loadFromFile("resurse/arial.ttf");
    sf::Text text(s, font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(x, y));
    window.draw(text);
}

void Engine::run(){
    srand((unsigned) time(0));

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "CannOnFire");

    sf::Time last_shoot = this->clock.getElapsedTime();
    sf::Time last_ball = this->clock.getElapsedTime();
    sf::Time start_time = this->clock.getElapsedTime();

    sf::Sprite background_sprite;
    background_sprite.setTexture(this->background_texture);

    int score = 0;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(auto& ball: this->balls)
            ball.move();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            this->tank.move("left");
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            this->tank.move("right");

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            sf::Time new_bullet_time = this->clock.getElapsedTime();
            if(new_bullet_time.asMilliseconds() - last_shoot.asMilliseconds() >= delay_bullets){
                this->tank.shoot();
                last_shoot = new_bullet_time;
            }
        }

        sf::Time new_ball_time = this->clock.getElapsedTime();
        if(new_ball_time.asMilliseconds() - last_ball.asMilliseconds() >= delay_balls || this->balls.size() == 0){
            this->balls.push_back(Ball());
            last_ball = new_ball_time;
        }

        this->tank.update(balls, score);
        // if(this->tank.check_hit(this->balls))
        //     std::cout<<"Tank was hit\n";

        window.clear();

        window.draw(background_sprite);
        this->tank.display(window);
        for(auto& ball: this->balls)
            ball.display(window);

        std::string s1 = "SCORE: ";
        std::string s2 = this->int_to_string(score);
        std::string s3 = s1 + s2;
        this->display_text(window, s3, 30, 30);

        sf::Time elapsed_time = clock.getElapsedTime();
        int seconds = (elapsed_time.asMilliseconds() - start_time.asMilliseconds()) / 1000;
        int secs = seconds % 60;
        int mins = seconds / 60;
        s1 = this->int_to_string(mins);
        s2 = this->int_to_string(secs);
        if(mins == 0)
            s3 = "TIME: " + s2 + " secs";
        else
            s3 = "TIME: " + s1 + " mins " + s2 + " secs";
        this->display_text(window, s3, 30, 70);


        window.display();
    }
}