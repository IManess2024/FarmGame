#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Each animation frame in the sprite sheet is 32 pixels wide and 32 pixels tall.
sf::Vector2i framesize(32, 32);

// Size of one bull animation frame in the bull sprite sheet.
sf::Vector2i bullsize(64, 64);

// Size of one chick animation frame in the chick sprite sheet.
sf::Vector2i chicksize(16, 16);

// This is how long one animation frame stays on screen before switching.
float animationFrameTime = 0.12f;

int main()
{
    // initialize randomizer
    std::srand(std::time(0));

    // Create the game window with a size of 800 by 600 pixels.
    sf::RenderWindow window(sf::VideoMode({800, 600}), "FarmGame");

    // Limit the game to 60 frames per second so movement stays smooth and stable.
    window.setFramerateLimit(60);

    // This texture stores the full turkey sprite sheet image in memory.
    sf::Texture turkey_sprite_sheet;

    // Load the turkey sprite sheet from the Textures folder.
    if (!turkey_sprite_sheet.loadFromFile("Textures/Turkey_animation_with_shadow.png"))
    {
        // If the file cannot be loaded, print an error message.
        std::cout << "ERROR" << std::endl;

        // Stop the program because the turkey sprite cannot be drawn without this texture.
        return 1;
    }

    // grass sprite loading

    sf::Texture grass_sprite_sheet;

    if (!grass_sprite_sheet.loadFromFile("Textures/1 Tiles/FieldsTile_38.png"))
    {
        std::cout << "ERROR" << std::endl;

        return 2;
    }
    sf::Sprite grass(grass_sprite_sheet);

    sf::Texture grass_particle;
    if (!grass_particle.loadFromFile("Textures/2 Objects/5 Grass/3.png"))
    {
        std::cout << "ERROR" << std::endl;

        return 3;
    }
    sf::Sprite smallgrass(grass_particle);
    smallgrass.setScale({2.0f, 2.0f});

    // stone sprite making

    sf::Texture stones_sprite_sheet;
    if (!stones_sprite_sheet.loadFromFile("Textures/2 Objects/4 Stone/11.png"))
    {
        std::cout << "ERROR" << std::endl;

        return 4;
    }
    sf::Sprite pebble(stones_sprite_sheet);

    // Load the bull sprite sheet and create the bull from its first frame.

    sf::Texture bull_sprite_sheet;

    if (!bull_sprite_sheet.loadFromFile("Textures/Bull_animation_with_shadow.png"))
    {
        std::cout << "ERROR" << std::endl;

        return 5;
    }

    // Load the texture for chicks
    sf::Texture chick_sprite_sheet;

    if (!chick_sprite_sheet.loadFromFile("Textures/Chick_animation_with_shadow.png"))
    {
        // If the file cannot be loaded, print an error message.
        std::cout << "ERROR" << std::endl;

        // Stop the program because the turkey sprite cannot be drawn without this texture.
        return 6;
    }
    

    std::array<sf::Sprite, 3> chicks = {
        sf::Sprite chick(chick_sprite_sheet, sf::IntRect({0, 0}, chicksize)),
        sf::Sprite chick(chick_sprite_sheet, sf::IntRect({0, 0}, chicksize)),
        sf::Sprite chick(chick_sprite_sheet, sf::IntRect({0, 0}, chicksize))
    };

    chicks[0].setPosition({420.f, 320.f});
    chicks[1].setPosition({610.f, 320.f});
    chicks[2].setPosition({630.f, 480.f});

    //This loop may not be necessary- will require some experimentation

    for (int i = 0; i < 3; i++)
    {
        chicks[i].setScale({1.5, 1.5});
    }
    

    // bull sprite

    sf::Sprite bull(bull_sprite_sheet, sf::IntRect({0, 0}, bullsize));

    // Scale the bull up so it matches the size of the fence pen on screen.
    bull.setScale({3.f, 3.f});

    // Start the bull inside the fenced area before random movement begins.
    bull.setPosition({500.f, 330.f});

    // horizontal fence loading

    sf::Texture horizontal_fence_sprite;

    if (!horizontal_fence_sprite.loadFromFile("Textures/2 Objects/2 Fence/1.png"))
    {
        std::cout << "ERROR" << std::endl;

        return 6;
    }
    sf::Sprite horizontalfence(horizontal_fence_sprite);
    horizontalfence.setScale({2.0f, 2.0f});

    // vertical fence loading

    sf::Texture vertical_fence_sprite;

    if (!vertical_fence_sprite.loadFromFile("Textures/2 Objects/2 Fence/7.png"))
    {
        std::cout << "ERROR" << std::endl;

        return 7;
    }
    sf::Sprite verticalfence(vertical_fence_sprite);
    verticalfence.setScale({2.0f, 2.0f});

    // Create the turkey sprite using the sprite sheet texture.
    // The IntRect chooses only the first 32x32 frame from the full sprite sheet.
    sf::Sprite turkey(turkey_sprite_sheet, sf::IntRect({0, 0}, framesize));

    // Scale the small 32x32 sprite up 4 times so it is easier to see in the window.
    turkey.setScale({1.7f, 1.7f});

    // Place the turkey near the middle-left area of the window at the start.
    turkey.setPosition({260.f, 180.f});

    // This timer counts how much time has passed since the last animation frame change.
    float anim_timer = 0.f;

    // This is the current column number in the sprite sheet animation.
    int animationframe = 0;

    // Row 0 in the sprite sheet shows the turkey facing down.
    int downRow = 0;

    // Row 1 in the sprite sheet shows the turkey facing up.
    int upRow = 1;

    // Row 2 in the sprite sheet shows the turkey facing left.
    int leftRow = 2;

    // Row 3 in the sprite sheet shows the turkey facing right.
    int rightRow = 3;

    // This is the movement speed of the turkey in pixels per second.
    float speed = 150.0f;

    // Stores the bull's current direction so it keeps walking the same way until the timer changes it.
    sf::Vector2f bullmove(1.f, 0.f);

    // Bull sprite sheet

    float bull_anim_timer = 0.f;
    int bull_animation_frame = 0;
    int bulldirectionrow = rightRow;

    // Counts down to the next random direction change for the bull.
    float bulltimer = 0.f;

    // Bull movement speed in pixels per second.
    float bullspeed = 45.f;

    // The clock measures the time between frames.
    sf::Clock clock;

    // This stores which row of the sprite sheet should be shown right now.
    int directionrow = 0;

    // Keep the game running while the window is open.
    while (window.isOpen())
    {
        // Read all window events, such as closing the window.
        while (const std::optional event = window.pollEvent())
        {
            // Check if the player clicked the close button.
            if (event->is<sf::Event::Closed>())
            {
                // Close the window and end the game loop.
                window.close();
            }
        }

        // This stores how far the turkey should move during this frame.
        sf::Vector2f movement(0.0f, 0.0f);

        // Restart the clock and get the time since the previous frame in seconds.
        float dt = clock.restart().asSeconds();

        bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
        bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
        bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
        bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        int pressedkeys = left + up + down + right;

        if (pressedkeys == 1)
        {
            // Check if W is pressed so the turkey moves up.
            if (up)
            {
                // Move up by subtracting from the y position.
                movement.y -= speed * dt;

                // Use the up-facing row from the sprite sheet.
                directionrow = upRow;
            }

            // Check if S is pressed so the turkey moves down.
            else if (down)
            {
                // Move down by adding to the y position.
                movement.y += speed * dt;

                // Use the down-facing row from the sprite sheet.
                directionrow = downRow;
            }

            // Check if A is pressed so the turkey moves left.
            else if (left)
            {
                // Move left by subtracting from the x position.
                movement.x -= speed * dt;

                // Use the left-facing row from the sprite sheet.
                directionrow = leftRow;
            }

            // Check if D is pressed so the turkey moves right.
            else if (right)
            {
                // Move right by adding to the x position.
                movement.x += speed * dt;

                // Use the right-facing row from the sprite sheet.
                directionrow = rightRow;
            }
        }

        // Animate only while the turkey is moving.
        if (movement.x != 0.f || movement.y != 0.f)
        {
            // Add this frame's time to the animation timer.
            anim_timer += dt;

            // Check if enough time has passed to show the next sprite frame.
            if (anim_timer >= animationFrameTime)
            {
                // Reset the timer before counting toward the next frame.
                anim_timer = 0.f;

                // Move to the next animation column, then loop back after frame 5.
                animationframe = (animationframe + 1) % 6;
            }
        }
        else
        {
            // If the turkey is not moving, show the first frame so it looks idle.
            animationframe = 0;

            // Reset the timer so the next movement starts cleanly.
            anim_timer = 0.f;
        }

        // Apply the movement calculated from the keyboard input.
        turkey.move(movement);

        // Choose the correct 32x32 rectangle from the sprite sheet.
        // X chooses the animation frame column, and Y chooses the direction row.
        turkey.setTextureRect(sf::IntRect({animationframe * framesize.x, directionrow * framesize.y}, framesize));

        // Clear the window then load grass tiles
        window.clear();
        for (int y = 0; y < 600; y += 32)
        {
            for (int x = 0; x < 800; x += 32)
            {
                grass.setPosition({float(x), float(y)});
                window.draw(grass);
            }
        }

        // Draw a few grass decoration sprites on top of the background.
        smallgrass.setPosition({120.f, 90.f});
        window.draw(smallgrass);
        smallgrass.setPosition({620.f, 160.f});
        window.draw(smallgrass);
        smallgrass.setPosition({380.f, 430.f});
        window.draw(smallgrass);

        // Draw a few stone decoration sprites on top of the background.
        pebble.setPosition({210.f, 360.f});
        window.draw(pebble);
        pebble.setPosition({520.f, 280.f});
        window.draw(pebble);
        pebble.setPosition({700.f, 470.f});
        window.draw(pebble);

        // Fence rectangle that also defines the bull's allowed movement area.

        float topfenceleft = 410.f;
        float topfencetop = 70.f;
        float topfencewidth = 300.f;
        float topfenceheight = 150.f;

        float fenceleft = 380.f;
        float fencetop = 260.f;
        float fencewidth = 360.f;
        float fenceheight = 300.f;
        // Distance between repeated fence sprites when drawing the pen border.
        float horizontalfencestep = horizontal_fence_sprite.getSize().x * horizontalfence.getScale().x;
        float verticalfencestep = vertical_fence_sprite.getSize().y * verticalfence.getScale().y;
        // Keeps the bull slightly inside the visible fence instead of touching the outer sprite edge.
        float fencemargin = 12.f;
        // Inner fence bounds used for collision checks.
        float insideleft = fenceleft + fencemargin;
        float insidetop = fencetop + fencemargin;
        float insideright = fenceleft + fencewidth - fencemargin;
        float insidebottom = fencetop + fenceheight + fencemargin;

        // Reduce the timer every frame; when it reaches zero the bull picks a new direction.
        bulltimer -= dt;

        if (bulltimer < 0.f)
        {
            // Choose one of four straight-line directions: right, left, down, or up.
            int direction = std::rand() % 4;
            if (direction == 0)
            {
                bullmove = {1.f, 0.f};
                bulldirectionrow = rightRow;
            }
            if (direction == 1)
            {
                bullmove = {-1.f, 0.f};
                bulldirectionrow = leftRow;
            }
            if (direction == 2)
            {
                bullmove = {0.f, 1.f};
                bulldirectionrow = downRow;
            }
            if (direction == 3)
            {
                bullmove = {0.f, -1.f};
                bulldirectionrow = upRow;
            }
            // Wait 1 to 3 seconds before choosing another random direction.
            bulltimer = 1.f + (std::rand() % 200) / 100.f;
        }

        bool bullmovement = bullmove.x != 0.f || bullmove.y != 0.f;

        if (bullmovement)
        {
            bull_anim_timer += dt;
            if (bull_anim_timer >= animationFrameTime)
            {
                bull_anim_timer = 0.f;
                bull_animation_frame = (bull_animation_frame + 1) % 6;
            }
        }
        else
        {
            bull_animation_frame = 0;
            bull_anim_timer = 0.f;
        }

        bull.setTextureRect(sf::IntRect({bull_animation_frame * bullsize.x, bulldirectionrow * bullsize.y}, bullsize));

        // Move the bull using frame time so its speed stays stable at different frame rates.
        bull.move({bullmove.x * bullspeed * dt, bullmove.y * bullspeed * dt});

        // Read the new position so collision correction can clamp it back inside the fence.
        sf::Vector2f bullpos = bull.getPosition();

        // Right and bottom limits subtract the scaled bull size so the whole sprite stays inside.
        float bullright = insideright - bullsize.x * bull.getScale().x;
        float bullbottom = insidebottom - bullsize.y * bull.getScale().y;

        // Tracks whether the bull touched the fence this frame.
        bool bullhitfence = false;

        if (bullpos.x < insideleft)
        {
            bullpos.x = insideleft;
            bullhitfence = true;
        }
        if (bullpos.x > bullright)
        {
            bullpos.x = bullright;
            bullhitfence = true;
        }
        if (bullpos.y < insidetop)
        {
            bullpos.y = insidetop;
            bullhitfence = true;
        }
        if (bullpos.y > bullbottom)
        {
            bullpos.y = bullbottom;
            bullhitfence = true;
        }

        // Apply the corrected position after all fence collision checks are finished.
        bull.setPosition(bullpos);

        if (bullhitfence)
        {
            // Force a new direction next frame so the bull does not keep pushing into the fence.
            bulltimer = 0.f;
        }

        auto drawfence = [&](float left, float top, float width, float height)
        {
            for (float x = left; x <= left + width; x += horizontalfencestep)
            {
                horizontalfence.setPosition({x, top});
                window.draw(horizontalfence);

                horizontalfence.setPosition({x, top + height});
                window.draw(horizontalfence);
            }

            for (float y = top; y <= top + height; y += verticalfencestep)
            {
                verticalfence.setPosition({left, y});
                window.draw(verticalfence);

                verticalfence.setPosition({left + width, y});
                window.draw(verticalfence);
            }
        };

        drawfence(topfenceleft, topfencetop, topfencewidth, topfenceheight);
        drawfence(fenceleft, fencetop, fencewidth, fenceheight);


                         // Draw the bull after movement and collision correction.
                         window.draw(bull);

        // Draw the turkey sprite after choosing its position and sprite sheet frame.
        window.draw(turkey);

        // Show everything that was drawn during this frame.
        window.display();
    }

    // Return 0 to say the program finished normally.
    return 0;
}
