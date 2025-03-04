#pragma once

namespace conf
{
    // Window configuration
    sf::Vector2u const window_size{1920u, 1080u};
    sf::Vector2f const window_size_f = static_cast<sf::Vector2f>(window_size); // Convert to float
    uint32_t const max_framerate = 60;
    float const dt = 1.0f / static_cast<float>(max_framerate);

    // Ball configuration
    float const radius = 10.0f;

} // namespace conf