#include "../Headers/Game.hpp"

// Non-meber Functions

sf::Color getTileColor(unsigned int tileType)
{
  switch (tileType)
  {
    case TileType::SAND:
      return sf::Color(252U, 219U, 129U);

    default:
      return sf::Color::White;
  }
}

// Initializers

void Game::initWindow()
{
  // Reading the window config file
  libconfig::Config windowConfig;
  try
  {
    windowConfig.readFile("config/Window.cfg");
  }
  catch (const libconfig::FileIOException &ioException)
  {
    std::cerr << "I/O error when reading the configuration file." << std::endl;
    return;
  }
  catch (const libconfig::ParseException &parseException)
  {
    std::cerr << "Parse error at " << parseException.getFile() << ": " << parseException.getLine()  << " - " << parseException.getError() << std::endl;
    return;
  }

  // Declaring the window properties as variables
  unsigned int windowWidth;
  unsigned int windowHeight;
  std::string windowTitle;
  unsigned int windowFps;
  bool windowVSync;

  // Loading the variables from the config file
  windowConfig.lookupValue("width", windowWidth);
  windowConfig.lookupValue("height", windowHeight);
  windowConfig.lookupValue("title", windowTitle);
  windowConfig.lookupValue("fps", windowFps);
  windowConfig.lookupValue("vsync", windowVSync);

  // Creating and setting up the window
  this->window = new sf::RenderWindow(
    sf::VideoMode(windowWidth, windowHeight),
    windowTitle,
    sf::Style::Titlebar | sf::Style::Close
  );
  this->window->setVerticalSyncEnabled(windowVSync);
  this->window->setFramerateLimit(windowFps);
}

// Constructor and Destructor

Game::Game()
{
  this->initWindow();

  for (int y = 0; y < GRID_HEIGHT; y++)
  {
    for (int x = 0; x < GRID_WIDTH; x++)
    {
      if (x + (y % 2) > GRID_WIDTH - 1) continue;
      if (x % 2 == 0)
      {
        this->tileGrid[y][x + y % 2].type = TileType::SAND;
      }
    }
  }
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

void Game::updatePhysics()
{
  if (tickTime < TICK_INTERVAL) return;

  for (int y = 0; y < GRID_HEIGHT; y++)
  {
    for (int x = 0; x < GRID_WIDTH; x++)
    {
      if (this->tileGrid[y][x].type == TileType::AIR) continue;

      switch (this->tileGrid[y][x].type)
      {
        case TileType::SAND:
          if (y + 1 > GRID_HEIGHT - 1 || this->tileGrid[y + 1][x].type != TileType::AIR)
            break;

          this->tileGrid[y][x].type = TileType::AIR;
          this->tileGrid[y + 1][x].type = TileType::SAND;
          break;

        default:
          break;
      }
    }
  }

  this->tickClock.restart();
}

void Game::updateClocks()
{
  this->tickTime = this->tickClock.getElapsedTime().asSeconds();
}

void Game::update()
{
  this->updateSFMLEvent();
  this->updateClocks();
  this->updatePhysics();
}

// Render Functions

void Game::renderGrid()
{
  sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));

  for (int y = 0; y < GRID_HEIGHT; y++)
  {
    for (int x = 0; x < GRID_WIDTH; x++)
    {
      if (this->tileGrid[y][x].type == TileType::AIR) continue;
      tile.setFillColor(getTileColor(this->tileGrid[y][x].type));
      tile.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
      this->window->draw(tile);
    }
  }
}

void Game::render()
{
  this->window->clear();
  this->renderGrid();
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
