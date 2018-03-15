#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "Entity.hpp"
#include "AnimatedSprite.hpp"
#include "Resources.hpp"

class Player : public Entity
{
public:

    Player();
    ~Player();

    enum Direction { F, R, L, B };

    void init();

    void update(const sf::Time& deltatime);

    void draw(sf::RenderWindow& window) const;

    //---
    //Attack functions

    void attack();

    sf::FloatRect getAttackBounds();

    void ult();

    //---
    //Movement machine

    void addKey(sf::Keyboard::Key key);
    void removeKey(sf::Keyboard::Key key);

    //---

    int getEnergy();
    void codePlaced();
    void minusEnergy();
    void addOneEnergy();

    void bugKilled();
    bool haveRedbull();
    void redbull();

    Player::Direction getDirection();


private:

    Resources _resources;

    const sf::Vector2f _playerSize = sf::Vector2f(64, 64);

    //---
    //Player

    enum Animations { WF, WR, WL, WB, SF, SR, SL, SB };

    Direction _direction;

    const float _playerVelocity = 0.2f;

    AnimatedSprite _player;

    //---
    //Attack

    bool _attaking;

    AnimatedSprite _lighting;

    sf::Sound _lightintSound;

    //---
    //Private movement functions

    void setAnimation(Animations animation);
    void setMovement(Direction direction, bool walking);

    //---
    //Propeties

    const int _redbullMaxCount = 20;
    int _redbullCount;

    bool _haveRedbull;

    const int _energyMax = 100;
    int _energy;

    //---
    //Movement Machine

    std::vector<sf::Keyboard::Key> _keys;

    void updateKeys();

    //---

};

#endif