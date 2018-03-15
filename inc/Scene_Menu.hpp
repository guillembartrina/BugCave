#ifndef SCENE__MENU_HPP
#define SCENE__MENU_HPP

#include "Scene.hpp"
#include "Resources.hpp"

class Scene_Menu : public Scene
{
public:

    Scene_Menu(SceneManager& sceneManager);
    ~Scene_Menu();

    void init();

    void handleEvents(const sf::Event& event);

    void update(const sf::Time deltatime);

    void draw(sf::RenderWindow& window) const;

    void pause();

    void resume();

private:

    Resources _resources;

    sf::Text textTitle;

    const int numItems = 2;

    sf::Text textPlay;
    sf::Text textExit;

    int currIndex;

    sf::Sprite spriteChar;

};

#endif