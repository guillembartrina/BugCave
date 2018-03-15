#include "Bug.hpp"

RandomGenerator Bug::_rndGen = RandomGenerator();

Bug::Bug(const sf::Vector2f& position)
{
    setPosition(position);
    setVelocity(sf::Vector2f(_rndGen.getRandFloat(-0.2f, 0.2f), _rndGen.getRandFloat(-0.2f, 0.2f)));
    setSize(sf::Vector2f(20, 20));

    _bug.setPosition(getPosition());
    _bug.setRadius(getSize().x/2);

    _bug.setFillColor(sf::Color::Green);
}

Bug::~Bug()
{

}

void Bug::update(const sf::Time& deltatime)
{
    setPosition(getPosition() + getVelocity() * float(deltatime.asMilliseconds()));
    _bug.setPosition(getPosition());
}

void Bug::draw(sf::RenderWindow& window) const
{
    window.draw(_bug); 
}

Bug Bug::cloneAndDivide()
{
    setVelocity(sf::Vector2f(-getVelocity().y, getVelocity().x));
    Bug tmp = *this;
    tmp.setVelocity(getVelocity() * -1.f);
    return tmp;
}