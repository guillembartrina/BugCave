
#include "Scene_Menu.hpp"

Scene_Menu::Scene_Menu(SceneManager& sceneManager) : Scene(sceneManager)
{
}

Scene_Menu::~Scene_Menu()
{
}

void Scene_Menu::init()
{
    textTitle.setFont(_resources.Font("font"));
    textTitle.setString("# BUG CAVE #");
    textTitle.setCharacterSize(90);
    textTitle.setFillColor(sf::Color::Yellow);
    textTitle.setPosition(86, 100);

    textPlay.setFont(_resources.Font("font"));
    textPlay.setString("PLAY");
    textPlay.setCharacterSize(60);
    textPlay.setFillColor(sf::Color::White);
    textPlay.setPosition(160, 300);

    textExit.setFont(_resources.Font("font"));
    textExit.setString("EXIT");
    textExit.setCharacterSize(60);
    textExit.setFillColor(sf::Color::White);
    textExit.setPosition(160, 400);

    currIndex = 0;

    spriteChar.setTexture(_resources.Texture("player"));
    spriteChar.setTextureRect(sf::IntRect(0, 64, 64, 64));
    spriteChar.setScale(4.f, 4.f);
    spriteChar.setPosition(400, 260);
}

void Scene_Menu::handleEvents(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Down:
                {
                    if(currIndex == 0) ++currIndex;
                }
                    break;
                case sf::Keyboard::Up:
                {
                    if(currIndex == 1) --currIndex;
                }
                    break;
                case sf::Keyboard::Return:
                {
                    if(currIndex == 0)
                    {
                        _sceneManager->addScene(Scenes::PLAY, false);
                    }
                    else if(currIndex == 1)
                    {
                        _sceneManager->popScene();
                    }
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case sf::Event::MouseButtonPressed:
        {

        }
            break;
        default:
            break;
    }
}

void Scene_Menu::update(const sf::Time deltatime)
{
    textPlay.setFillColor(sf::Color::White);
    textExit.setFillColor(sf::Color::White);

    if(currIndex == 0)
    {
        textPlay.setFillColor(sf::Color::Green);
    }
    else if(currIndex == 1)
    {
        textExit.setFillColor(sf::Color::Green);
    }
}

void Scene_Menu::draw(sf::RenderWindow& window) const
{
    window.draw(textTitle);
    window.draw(textPlay);
    window.draw(textExit);
    window.draw(spriteChar);
}

void Scene_Menu::pause()
{

}

void Scene_Menu::resume()
{

}
