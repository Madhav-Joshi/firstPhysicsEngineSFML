#include "events/events.hpp"
#include <optional>

void processEvents(sf::Window &window)
{
    while (const std::optional event = window.pollEvent())
{
    // Window closed or escape key pressed: exit
    if (event->is<sf::Event::Closed>() ||
        (event->is<sf::Event::KeyPressed>() &&
         event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
        window.close();
}
}