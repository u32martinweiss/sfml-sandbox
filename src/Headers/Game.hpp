#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <libconfig.h++>
#include <iostream>

class Game {
  private:
    sf::RenderWindow* window;
    sf::Event sfEvent;

    // Initializers
    void initWindow();

  public:
    // Constructor and Destructor
    Game();
    virtual ~Game();

    // Update Functions
    void updateSFMLEvent();
    void update();

    // Render Functions
    void render();

    // Functions
    void run();
};

#endif // GAME_HPP
