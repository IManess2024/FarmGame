#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Template");
    window.setFramerateLimit(60);

    sf::CircleShape circle(80.f);
    circle.setFillColor(sf::Color(100, 180, 255));
    circle.setPosition({260.f, 180.f});

    sf::Texture turkey_sprite_sheet;
    if(!turkey_sprite_sheet.loadFromFile("Textures/Turkey_animation_with_shadow.png"))
    {
        //Handle the error
        std::cout << "ERROR" << std::endl;

    }

    sf::Sprite turkey(turkey_sprite_sheet);
    turkey.setPosition({0.0f, 0.0f});


    sf::IntRect frame_1({320, 1232},{28, 32});
    sf::IntRect frame_2({320, 1232},{28, 32});
    sf::IntRect frame_3({320, 1232},{28, 32});
    sf::IntRect frame_4({320, 1232},{28, 32});
    sf::IntRect frame_5({320, 1232},{28, 32});

    std::vector<sf::IntRect> all_frames;
    all_frames.push_back(frame_1);
    all_frames.push_back(frame_2);
    all_frames.push_back(frame_3);
    all_frames.push_back(frame_4);
    all_frames.push_back(frame_5);

    unsigned int idx = 0;
    float anim_timer = 0.f;
    float const anim_speed = 1.0f;
    





//local variables

float speed = 300.0f;
sf::Clock clock;


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // Here is the character movement

sf::Vector2f movement (0.0f, 0.0f);

float dt = clock.restart().asSeconds();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            // left key is pressed: move our character
            movement.x -= speed*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            // left key is pressed: move our character
            movement.y -= speed*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            // left key is pressed: move our character
            movement.y += speed*dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            // left key is pressed: move our character
            movement.x += speed*dt;
        }
circle.move(movement);


        //Final operations

        window.clear(sf::Color(30, 30, 40));
        window.draw(turkey);
        window.draw(circle);
        window.display();
    }
}
