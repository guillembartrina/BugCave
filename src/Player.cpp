#include "Player.hpp"

Player::Player()
{

}

Player::~Player()
{
    _resources.Music("music").stop();
}

void Player::init()
{
    setPosition(sf::Vector2f(100, 100));
    setSize(_playerSize);
    _player.setPosition(getPosition());

    _player.addAnimation(_resources.Texture("player"), 4, 2, sf::Vector2u(_playerSize), sf::seconds(0.125f), true); //Direction::F
    _player.addAnimation(_resources.Texture("player"), 4, 1, sf::Vector2u(_playerSize), sf::seconds(0.125f), true); //Direction::R
    _player.addAnimation(_resources.Texture("player"), 4, 0, sf::Vector2u(_playerSize), sf::seconds(0.125f), true); //Direction::L
    _player.addAnimation(_resources.Texture("player"), 4, 3, sf::Vector2u(_playerSize), sf::seconds(0.125f), true); //Direction::B

    setMovement(Direction::F, false);

    _lighting.addAnimation(_resources.Texture("attack"), 5, sf::Vector2u(78, 64), sf::seconds(0.075f), false);
    _lighting.setOrigin(16, 32);
    _lighting.setScale(2.f, 1.f);

    _lighting.setActiveAnimation(0, false);

    _lightintSound.setBuffer(_resources.Sound("attack_sound"));
    _lightintSound.setPitch(2.f);

    _attaking = false;

    _energy = 70;

    _redbullCount = 0;

    _haveRedbull = false;

    _resources.Music("music").play();
}

void Player::update(const sf::Time& deltatime)
{
    if(_redbullCount >= _redbullMaxCount)
    {
        _haveRedbull = true;
    }

    if(!_attaking)
    {
        setPosition(getPosition() + getVelocity() * float(deltatime.asMilliseconds())); //update entity pos

        _player.setPosition(getPosition()); //update animation pos

        _player.updateAnimation(deltatime); //update animation
    }
    else
    {
        _lighting.updateAnimation(deltatime); //update lighting

        if(_lighting.hasAnimationEnded())
        {
            _attaking = false;
            _lighting.firstFrame();
            updateKeys();
        }
    }
    
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(_player);
    if(_attaking) window.draw(_lighting);
}

void Player::attack() //attack funct
{
    if(_attaking) return;

    _attaking = true;

    _player.nextFrame();

    _lighting.setPosition(getCenter());

    _lighting.playAnimation();

    _lightintSound.play();

}

sf::FloatRect Player::getAttackBounds()
{
    return _lighting.getGlobalBounds();
}

void Player::ult() //attack funct
{
    if(_attaking) return;

    _attaking = true;

    _player.nextFrame();

    //ULT CODE

}

void Player::setAnimation(Animations animation) //sets animation from Animations enum
{
    if(animation < 4)
    {
        _player.setActiveAnimation(animation);
    }
    else
    {
        _player.setActiveAnimation(animation - 4, false);
    }
}

void Player::setMovement(Direction direction, bool walking) //sets movement from direction and walking bool
{
    _direction = direction;

    if(walking)
    {
        switch(direction)
        {
            case F:
                setVelocity(sf::Vector2f(0, _playerVelocity));
                _lighting.setRotation(90.f);
                break;
            case R:
                setVelocity(sf::Vector2f(_playerVelocity, 0));
                _lighting.setRotation(0.f);
                break;
            case L:
                setVelocity(sf::Vector2f(-_playerVelocity, 0));
                _lighting.setRotation(180.f);
                break;
            case B:
                setVelocity(sf::Vector2f(0, -_playerVelocity));
                _lighting.setRotation(270.f);
                break;
        }

        setAnimation(Animations(direction));
    }
    else
    {
        setVelocity(sf::Vector2f(0, 0));
        setAnimation(Animations(direction + 4));
    }
}

//-----

void Player::addKey(sf::Keyboard::Key key) //add a keyoard key to vector
{
    _keys.push_back(key);
    if(!_attaking) updateKeys();
}

void Player::removeKey(sf::Keyboard::Key key) //removes the releades key from vector
{
    bool found = false;

    for(int i = 0; !found && i < int(_keys.size()); ++i)
    {
        if(_keys[i] == key)
        {
            std::vector<sf::Keyboard::Key>::iterator it = _keys.begin();
            it += i;
            _keys.erase(it);
            found = true;
        }
    }

    if(!_attaking) updateKeys();
}

void Player::updateKeys() //get the last key of vector and extract movement
{
    if(_keys.empty())
    {
        setMovement(_direction, false);
    }
    else
    {
        switch(_keys.back())
            {
                case sf::Keyboard::Down:
                    setMovement(Direction::F, true);
                    break;
                case sf::Keyboard::Right:
                    setMovement(Direction::R, true);
                    break;
                case sf::Keyboard::Left:
                    setMovement(Direction::L, true);
                    break;
                case sf::Keyboard::Up:
                    setMovement(Direction::B, true);
                    break;
                default:
                    break;
            }
    }
}

//---

int Player::getEnergy()
{
    return _energy;
}

void Player::codePlaced()
{
    _energy -= 10;
}

void Player::minusEnergy()
{
    _energy -= 5;
}

void Player::addOneEnergy()
{
    if(_energy < 100) ++_energy;
}

bool Player::haveRedbull()
{
    return _haveRedbull;
}

void Player::bugKilled()
{
    if(!_haveRedbull) ++_redbullCount;

    if(_redbullCount >= _redbullMaxCount)
    {
        _haveRedbull = true;
        _redbullCount = 0;
    }
}

void Player::redbull()
{
    _haveRedbull = false;
}

Player::Direction Player::getDirection()
{
    return _direction;
}
