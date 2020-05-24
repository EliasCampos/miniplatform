#include <SFML/Graphics.hpp>

#include "includes/miniplatform/effect.h"
#include "includes/miniplatform/game.h"
#include "includes/miniplatform/settings.h"


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simple Platformer");

    // regulate the speed of the game via frame frames:
    sf::Clock clock;
    float frame;

    Game game;

    // run the program as long as the window is open
    while (window.isOpen())
    {

        frame = (float)clock.getElapsedTime().asMicroseconds() / 800;
        clock.restart();

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        game.update_state(frame);


        // clear the window with black color
        window.clear(sf::Color::White);

        // draw everything here...

        game.render(window);

        // end the current frame
        window.display();
    }

    return 0;
}
