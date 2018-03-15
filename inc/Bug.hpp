#ifndef BUG_HPP
#define BUG_HPP

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "Entity.hpp"
#include "AnimatedSprite.hpp"
#include "Resources.hpp"
#include "RandomGenerator.hpp"

class Bug : public Entity
{
public:

    Bug(const sf::Vector2f& position);
    ~Bug();

    void init();

    void update(const sf::Time& deltatime);

    void draw(sf::RenderWindow& window) const;

    Bug cloneAndDivide();

private:

    static RandomGenerator _rndGen;

    sf::CircleShape _bug;

};

#endif