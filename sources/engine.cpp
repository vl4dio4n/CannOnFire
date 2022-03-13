//
// Created by vladi on 3/9/2022.
//

#include "../headers/engine.hpp"
#include <iostream>

int Engine::delay_bullets = 100;
int Engine::delay_balls = 20000;
int Engine::window_width = 900;
int Engine::window_height = 1050.0;

Engine::Engine(){
    balls.push_back(Ball());
    background_texture.loadFromFile("resurse/background.jpg");
}

Engine::~Engine(){
    this->balls.clear();
    this->buttons.clear();
    std::cout << "Joaca s-a terminat\n";
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

void Engine::reset_game() {
    balls.clear();
    tank.reset_tank();
}

void Engine::run(){
    std::string game_state = "start";

    srand((unsigned) time(0));

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "CannOnFire");

    sf::Time last_shoot, last_ball, start_time, start_pause, end_pause;
    int total_paused_time;

    sf::Sprite background_sprite;
    background_sprite.setTexture(this->background_texture);

    sf::Color fill_color(85, 84, 3, 204);
    sf::Color outline_color(0, 0 , 0);
    sf::Color text_color(30, 10, 62, 204);

    sf::Color fill_color_hover(115, 191, 40, 204);
    sf::Color outline_color_hover(26, 27, 24, 204);
    sf::Color text_color_hover(30, 2, 73, 204);

    sf::Vector2f pos_new_game(350, 400);
    sf::Vector2f pos_main_menu(350, 400);
    sf::Vector2f pos_resume(350, 330);
    sf::Vector2f pos_quit(350, 470);
    sf::Vector2f pos_pause(800, 30);
    sf::Vector2f pos_end(150, 450);

    buttons.push_back(std::make_pair(Button{200, 50, 5.0, pos_new_game, "NEW GAME", fill_color, outline_color, text_color}, std::vector<std::string>({"start"}) ));
    buttons.push_back(std::make_pair(Button{200, 50, 5.0, pos_quit, "QUIT", fill_color, outline_color, text_color}, std::vector<std::string>({"paused", "start"})));
    buttons.push_back(std::make_pair(Button{75, 30, 3.0, pos_pause, "PAUSE", fill_color, outline_color, text_color}, std::vector<std::string>({"on"})));
    buttons.push_back(std::make_pair(Button{200, 50, 3.0, pos_main_menu, "MAIN MENU", fill_color, outline_color, text_color}, std::vector<std::string>({"paused"})));
    buttons.push_back(std::make_pair(Button{200, 50, 3.0, pos_resume, "RESUME", fill_color, outline_color, text_color}, std::vector<std::string>({"paused"})));
    buttons.push_back(std::make_pair(Button{600, 150, 3.0, pos_end, "You Lost!!! " , fill_color, outline_color, text_color}, std::vector<std::string>({"ended"})));

    int score = 0;

    while (window.isOpen())
    {
        if(game_state == "start"){
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    for(auto& btn: buttons){
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if (std::find(btn.second.begin(), btn.second.end(), game_state) != btn.second.end() && btn.first.check_hover(sf::Vector2f((float)mouse_pos.x, (float)mouse_pos.y))){
                            if(btn.first.get_text() == "NEW GAME") {
                                game_state = "on";
                                clock.restart();
                                last_shoot = clock.getElapsedTime();
                                last_ball = clock.getElapsedTime();
                                start_time = clock.getElapsedTime();
                                total_paused_time = 0;
                            }
                            else if(btn.first.get_text() == "QUIT")
                                window.close();
                            break;
                        }
                    }
                }
            }
            window.clear();
            window.draw(background_sprite);
        } else if(game_state == "on"){
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    Button btn = buttons[2].first;
                    if(btn.check_hover(sf::Vector2f((float)mouse_pos.x, (float)mouse_pos.y))) {
                        game_state = "paused";
                        start_pause = clock.getElapsedTime();
                    }
                }
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

            window.clear();

            window.draw(background_sprite);

            if(this->tank.check_hit(this->balls)) {
                game_state = "ended";
                tank.set_score(score);
                std::cout << tank;
            }
            else {
                this->tank.display(window);
                for (auto &ball: this->balls)
                    ball.display(window);

                std::string s1 = "SCORE: ";
                std::string s2 = this->int_to_string(score);
                std::string s3 = s1 + s2;
                this->display_text(window, s3, 30, 30);

                sf::Time elapsed_time = clock.getElapsedTime();
                int seconds = (elapsed_time.asMilliseconds() - start_time.asMilliseconds() - total_paused_time) / 1000;
                int secs = seconds % 60;
                int mins = seconds / 60;
                s1 = this->int_to_string(mins);
                s2 = this->int_to_string(secs);
                if (mins == 0)
                    s3 = "TIME: " + s2 + " secs";
                else
                    s3 = "TIME: " + s1 + " mins " + s2 + " secs";
                this->display_text(window, s3, 30, 70);
            }
        }
        else if(game_state == "paused"){
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    for(auto& btn: buttons){
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if (std::find(btn.second.begin(), btn.second.end(), game_state) != btn.second.end() && btn.first.check_hover(sf::Vector2f((float)mouse_pos.x, (float)mouse_pos.y))){
                            if(btn.first.get_text() == "MAIN MENU") {
                                game_state = "start";
                                score = 0;
                                reset_game();
                            }
                            else if(btn.first.get_text() == "QUIT")
                                window.close();
                            else if(btn.first.get_text() == "RESUME") {
                                game_state = "on";
                                end_pause = clock.getElapsedTime();
                                total_paused_time += (end_pause.asMilliseconds() - start_pause.asMilliseconds());
                                last_shoot += (end_pause - start_pause);
                                last_ball += (end_pause - start_pause);
                            }
                            break;
                        }
                    }
                }
            }
            window.clear();
            window.draw(background_sprite);
        } else if(game_state == "ended"){
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                    game_state = "start";
                    score = 0;
                    reset_game();
                }
            }

            window.clear();
            window.draw(background_sprite);
        }
        for(auto& btn: buttons) {
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            if (std::find(btn.second.begin(), btn.second.end(), game_state) != btn.second.end() && btn.first.check_hover(sf::Vector2f((float)mouse_pos.x, (float)mouse_pos.y))){
                btn.first.set_fill_color(fill_color_hover);
                btn.first.set_outline_color(outline_color_hover);
                btn.first.set_text_color(text_color_hover);
            } else{
                btn.first.set_fill_color(fill_color);
                btn.first.set_outline_color(outline_color);
                btn.first.set_text_color(text_color);
            }
        }
        for(auto& btn: buttons)
            if(std::find(btn.second.begin(), btn.second.end(), game_state) != btn.second.end())
                btn.first.display(window);
        window.display();
    }
}

std::ostream& operator<<(std::ostream& os, const Engine& engine){
    os << "Distractia s-a terminat!\n" << "\tJoaca a durat  " << engine.clock.getElapsedTime().asSeconds() / 60 << " minutes";
    return os;
}