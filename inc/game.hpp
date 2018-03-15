#ifndef GAME_HPP
#define GAME_HPP

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "Resources.hpp"
#include "SceneManager.hpp"

class Game  {
public:
  void run();

  static const int _scrW;
  static const int _scrH;
  static const std::string _scrT;

private:
  
  sf::RenderWindow _window;
  sf::Clock _clk;

  void init();
  void mainLoop();

  void update();
  void draw();
  void handleEvents();

private:

  SceneManager _scenes;

  Resources _resources;

};

#endif