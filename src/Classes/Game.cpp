#include "../Headers/Game.hpp"

// Constructor and Destructor

Game::Game()
{
  // Creating the SFML Window
  this->window = new sf::RenderWindow(
    sf::VideoMode(800, 600),
    "SFML"
  );
  this->window->setFramerateLimit(60);
  this->window->setVerticalSyncEnabled(false);
}

Game::~Game()
{
  delete this->window;
}

// Update Functions

void Game::updateSFMLEvent()
{
  while (this->window->pollEvent(this->sfEvent))
  {
    switch (this->sfEvent.type) {
      case sf::Event::Closed:
        this->window->close();
        break;

      default:
        break;
    }
  }
}

void Game::update()
{
  this->updateSFMLEvent();
}

// Render Functions

void Game::render()
{
  this->window->clear();
  this->window->display();
}

// Functions

void Game::run()
{
  while (this->window->isOpen())
  {
    this->update();
    this->render();
  }
}
