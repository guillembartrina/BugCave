#include "game.hpp"

const int Game::_scrW  = 800;
const int Game::_scrH = 800;
const std::string Game::_scrT = "Bug cave";

void Game::run()
{
  init();
  mainLoop();
}

void Game::init()
{
  _window.create(sf::VideoMode(_scrW, _scrH), _scrT);
  _window.setFramerateLimit(60);
  _window.setKeyRepeatEnabled(false);

  _scenes.init(); //Scenes init (MENU)

  _clk.restart();
}

void Game::mainLoop()
{
  while (_window.isOpen())
  {
    handleEvents();

    update();

    draw();

    _scenes.applySceneRequests(); //Scene handle
    if(_scenes.exitRequest()) _window.close(); //Exit request from scene?
  }
}

void Game::update()
{
  sf::Time deltatime;
  deltatime = _clk.restart();

  _scenes.activeScene().update(deltatime);
}

void Game::draw()
{
  _window.clear(sf::Color::Black);

  _scenes.activeScene().draw(_window); //Scene draw function

  _window.display();
}

void Game::handleEvents()
{
  sf::Event event;

  while (_window.pollEvent(event))
  {

    if (event.type == sf::Event::Closed)
    {
      _window.close();
    }
    else if (event.type == sf::Event::KeyPressed)
    {
      switch (event.key.code)
      {
        case sf::Keyboard::Escape:
          _window.close();
          break;

        default:
          break;
      }
    }

    _scenes.activeScene().handleEvents(event); //scene event handle

  }
}
