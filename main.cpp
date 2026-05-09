#include <SFML/Graphics.hpp>
#include <iostream>

sf::Vector2i framesize(32,32);
    float animationFrameTime = 0.12f;


int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Template");
    window.setFramerateLimit(60);

    

    

    sf::Texture turkey_sprite_sheet;
    if(!turkey_sprite_sheet.loadFromFile("Textures/Turkey_animation_with_shadow.png"))
    {
        //Handle the error
        std::cout << "ERROR" << std::endl;
        return 1;

    }

    sf::Sprite turkey(turkey_sprite_sheet, sf::IntRect({0,0}, framesize));

    turkey.setScale({4.f,4.f});
turkey.setPosition({260.f, 180.f});

   

    unsigned int idx = 0;
    float anim_timer = 0.f;
    float const anim_speed = 1.0f;
    int animationframe = 0;

int downRow = 0;
     int upRow = 1;
     int leftRow = 2;
     int rightRow = 3;




//local variables

float speed = 300.0f;
sf::Clock clock;
int directionrow = 0;

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
            directionrow = leftRow;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            // left key is pressed: move our character
            movement.y -= speed*dt;
            directionrow = upRow;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            // left key is pressed: move our character
            movement.y += speed*dt;
            directionrow = downRow;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            // left key is pressed: move our character
            movement.x += speed*dt;
            directionrow = rightRow;
        }

// Animate only while moving.
        if (movement.x != 0.f || movement.y != 0.f)
        {
            anim_timer += dt;
            if (anim_timer >= animationFrameTime)
            {
                anim_timer = 0.f;
                animationframe = (animationframe + 1) % 6;
            }
        }
        else
        {
            animationframe = 0;
            anim_timer = 0.f;
        }

turkey.move(movement);
turkey.setTextureRect(sf::IntRect({animationframe*framesize.x, directionrow*framesize.y}, framesize));


        //Final operations

        window.clear(sf::Color(30, 30, 40));
        window.draw(turkey);
        window.display();
    }

    return 0;
}
