#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <libconfig.h++>
#include <iostream>

#include "../Structs/Tile.hpp"
#include "../Constants.hpp"

class Game {
  private:
    sf::RenderWindow* window;
    sf::Event sfEvent;
    Tile tileGrid[GRID_HEIGHT][GRID_WIDTH];

    // Initializers
    void initWindow();

  public:
    // Constructor and Destructor
    Game();
    virtual ~Game();

    // Clocks
    sf::Clock tickClock;
    float tickTime;

    // Update Functions
    void updateSFMLEvent();
    void updateClocks();
    void updatePhysics();
    void update();

    // Render Functions
    void renderGrid();
    void render();

    // Functions
    void run();
};

#endif // GAME_HPP
