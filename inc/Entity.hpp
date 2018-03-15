#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cmath>

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"

class Entity
{
public:

    Entity();
    Entity(unsigned int id, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Vector2f& velocity);
	
    ~Entity();

    unsigned int getID() const;

    void setPosition(const sf::Vector2f& position);
	void setSize(const sf::Vector2f& size);
	void setVelocity(const sf::Vector2f& velocity);

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
	sf::Vector2f getVelocity() const;
	
    sf::Vector2f getCenter() const;

    sf::FloatRect getHitbox() const;

    float angleTo(const sf::Vector2f& to) const;
    float angleTo(const Entity& to) const;
    float angleFrom(const sf::Vector2f& from) const;
    float angleFrom(const Entity& to) const;

    float distance(const sf::Vector2f& other) const;
	float distance(const Entity& from) const;

    sf::Vector2f directionTo(const sf::Vector2f& to) const;
    sf::Vector2f directionTo(const Entity& to) const;
    sf::Vector2f directionFrom(const sf::Vector2f& from) const;
    sf::Vector2f directionFrom(const Entity& to) const;

    bool inRange(const sf::Vector2f& other, float range) const;
    bool inRange(const Entity& other, float range) const;

private:

    unsigned int ID;

	sf::Vector2f _position;
    sf::Vector2f _size;
    sf::Vector2f _velocity;
	
};

#endif