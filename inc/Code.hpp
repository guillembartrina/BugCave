#ifndef CODE_HPP
#define CODE_HPP

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "Entity.hpp"
#include "Resources.hpp"
#include "RandomGenerator.hpp"
#include "Player.hpp"

class Code : public Entity
{
public:

    Code();
    Code(const sf::Vector2f& position, const int energy);
    ~Code();

    void update();

    void draw(sf::RenderWindow& window) const;

    bool hit();

    static const sf::Vector2f& getWH();

private:
    
    static RandomGenerator _rnd;

    Resources _resources;

    static const sf::Vector2f _rectangleSize;
    static const int _maxLife;
    int _life;

    sf::RectangleShape _code;

    sf::Text _textCode;

};

#endif
