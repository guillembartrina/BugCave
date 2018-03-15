
#define _USE_MATH_DEFINES

#include "Entity.hpp"

Entity::Entity()
{
    ID = 0;
    _position = sf::Vector2f(0, 0);
    _size = sf::Vector2f(0, 0);
    _velocity = sf::Vector2f(0.f, 0.f);
}

Entity::Entity(unsigned int id, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& velocity)
{
    ID = id;
    _position = position;
    _size = size;
    _velocity = velocity;
}

Entity::~Entity()
{
}

unsigned int Entity::getID() const
{
    return ID;
}

void Entity::setPosition(const sf::Vector2f& position)
{
    _position = position;
}

void Entity::setSize(const sf::Vector2f& size)
{
    _size = size;
}

void Entity::setVelocity(const sf::Vector2f& velocity)
{
    _velocity = velocity;
}

sf::Vector2f Entity::getPosition() const
{
    return _position;
}

sf::Vector2f Entity::getSize() const
{
    return _size;
}

sf::Vector2f Entity::getVelocity() const
{
    return _velocity;
}

sf::Vector2f Entity::getCenter() const
{
    return sf::Vector2f(_position.x + _size.x/2, _position.y + _size.y/2);
}

sf::FloatRect Entity::getHitbox() const
{
    return sf::FloatRect(_position, _size);
}

float Entity::angleTo(const sf::Vector2f& to) const
{
    float angle =  atan2f( abs(to.y - getCenter().y), abs(to.x - getCenter().x));

    if(to.x >= getCenter().x)
    {
        if(to.y > getCenter().y)
        {
            angle = 2 * M_PI - angle; 
        }
        else
        {
            //nothing
        }
    }
    else
    {
        if(to.y > getCenter().y)
        {
            angle = M_PI + angle; 
        }
        else
        {
            angle = M_PI - angle;          
        }
    }

    return angle;
}

float Entity::angleTo(const Entity& to) const
{
    return angleTo(to.getCenter());
}

float Entity::angleFrom(const sf::Vector2f& from) const
{
    float angle = angleTo(from);

    if(angle > M_PI) angle = angle - M_PI;
    else angle = angle + M_PI;

    return angle;
}

float Entity::angleFrom(const Entity& from) const
{
    return angleFrom(from.getCenter());
}

float Entity::distance(const sf::Vector2f& other) const
{
    return sqrt(pow(getCenter().x - other.x, 2) + pow(getCenter().y - other.y, 2));
}

float Entity::distance(const Entity& other) const
{
    return distance(other.getCenter());
}

sf::Vector2f Entity::directionTo(const sf::Vector2f& to) const
{
    return (sf::Vector2f(to.x - getCenter().x, to.y - getCenter().y) / distance(to));
}

sf::Vector2f Entity::directionTo(const Entity& to) const
{
    return directionTo(to.getCenter());
}

sf::Vector2f Entity::directionFrom(const sf::Vector2f& from) const
{
    return (sf::Vector2f(getCenter().x - from.x, getCenter().y - from.y) / distance(from));
}

sf::Vector2f Entity::directionFrom(const Entity& from) const
{
    return directionFrom(from.getCenter());
}

bool Entity::inRange(const sf::Vector2f& other, float range) const
{
    return (distance(other) <= range);
}

bool Entity::inRange(const Entity& other, float range) const
{
    return (distance(other) <= range);
}