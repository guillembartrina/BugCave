
#include "Scene_Play.hpp"
#include "game.hpp" //to get window W and H

Scene_Play::Scene_Play(SceneManager& sceneManager) : Scene(sceneManager)
{
}

Scene_Play::~Scene_Play()
{
}

void Scene_Play::init()
{
    _spriteBackground.setTexture(_resources.Texture("background"));
    _spriteBackground.setColor(sf::Color(139, 69, 19));

    _player.init();

    _score = 0;

    _textScore.setFont(_resources.Font("font"));
    _textScore.setString("SCORE: " + std::to_string(_score));
    _textScore.setFillColor(sf::Color::Green);
    _textScore.setPosition(60, 40);

    _textEnergy.setFont(_resources.Font("font"));
    _textEnergy.setString("ENERGY: " + std::to_string(_player.getEnergy()));
    _textEnergy.setFillColor(sf::Color::Blue);
    _textEnergy.setPosition(60, 60);

    _textRedbull.setFont(_resources.Font("font"));
    _textRedbull.setString("REDBULL");
    _textRedbull.setFillColor(sf::Color::Red);
    _textRedbull.setPosition(620, 60);

    _codeMap = std::vector< std::vector<bool> >(int(Game::_scrW / Code::getWH().x), std::vector<bool>(int(Game::_scrH / Code::getWH().y), false));

    _touching = -1;

    _currentTime = sf::Time::Zero;
}

void Scene_Play::handleEvents(const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Down:
                case sf::Keyboard::Right:
                case sf::Keyboard::Left:
                case sf::Keyboard::Up:
                    _player.addKey(event.key.code);
                    break;
                case sf::Keyboard::Space:
                    _player.attack();
                    checkAttackKill();
                    break;
                case sf::Keyboard::V:
                {   
                    if(_player.haveRedbull())
                    { 
                        _bugs.clear();
                        _player.redbull();
                    }
                    addRndBug(false, 2);
                }
                    break;
                case sf::Keyboard::C:
                {
                    if(_player.getEnergy() >= 20)
                    {
                        Code tmp;
                        sf::Vector2f pos = sf::Vector2f( int(_player.getCenter().x / tmp.getSize().x), int(_player.getCenter().y / tmp.getSize().y));
                        
                        //Player::Direction dir = _player.getDirection();

                        /*  code change position
                            if(dir == Player::Direction::F) ++pos.y;
                            else if(dir == Player::Direction::B) --pos.y;
                            else if(dir == Player::Direction::R) ++pos.x;
                            else if(dir == Player::Direction::L) --pos.x;
                        */

                        if(!_codeMap[pos.x][pos.y])
                        {
                            _codes.push_back(Code(pos, _player.getEnergy()));
                            _codeMap[pos.x][pos.y] = true;
                            addRndBug(false, 8);
                            _player.codePlaced();
                        }
                    }
                }  
                    break;
                default:
                    break;
            }
        }
            break;

        case sf::Event::KeyReleased:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Down:
                case sf::Keyboard::Right:
                case sf::Keyboard::Left:
                case sf::Keyboard::Up:
                    _player.removeKey(event.key.code);
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
}

void Scene_Play::update(const sf::Time deltatime)
{
    if(_score >= 30) _sceneManager->popScene();

    _score = _codes.size();

    _currentTime += deltatime;

    if(_currentTime >= _nextEnergy)
    {
        _currentTime -= _nextEnergy;
        _player.addOneEnergy();
        addRndBug(false, 2);
    }

    if(_player.haveRedbull()) _textRedbull.setFillColor(sf::Color::Green);
    else _textRedbull.setFillColor(sf::Color::Red);

    handleBugs(deltatime);

    _textScore.setString("SCORE: " + std::to_string(_score));

    _textEnergy.setString("ENERGY: " + std::to_string(_player.getEnergy()));

    _player.update(deltatime);
}

void Scene_Play::draw(sf::RenderWindow& window) const
{
    window.draw(_spriteBackground);

    for(unsigned int i = 0; i < _codes.size(); ++i)
    {
       _codes[i].draw(window);
    }

    for(unsigned int i = 0; i < _bugs.size(); ++i)
    {
       _bugs[i].draw(window);
    }

    window.draw(_textScore);
    window.draw(_textEnergy);
    window.draw(_textRedbull);

    _player.draw(window);
}

void Scene_Play::pause()
{

}

void Scene_Play::resume()
{

}

void Scene_Play::addRndBug(bool add, int prob)
{
    bool go = false;

    if(add)
    {
        go = true;
    }
    else
    {
        int base = 10;
        if(_bugs.size() > 10) base -= 2;
        int rndInt = _rndGen.getRandInt(0, base + _player.getEnergy()/10);

        if(rndInt < prob)
        {
            go = true;
        }
    }
    
    if(go)
    {
        sf::Vector2f rndPos;

        bool repeat;

        do{
            rndPos = sf::Vector2f(_rndGen.getRandInt(50, 750), _rndGen.getRandInt(50, 750));

            repeat = false;

            for(unsigned int i = 0; i < _codes.size() && !repeat; ++i)
            {
                repeat = _codes[i].getHitbox().contains(rndPos);
            }

        }while(repeat);

        _bugs.push_back(Bug(rndPos));
    }
}

void Scene_Play::handleBugs(const sf::Time deltatime)
{
    for(unsigned int i = 0; i < _bugs.size(); ++i)
    {
        _bugs[i].update(deltatime);

        if(_player.getEnergy() > 0 && _touching == -1 && _player.getHitbox().intersects(_bugs[i].getHitbox())) { _player.minusEnergy(); _touching = i; }
        else if(_touching == int(i) && !_player.getHitbox().intersects(_bugs[i].getHitbox())) _touching = -1;

        bool del = false;

        for(unsigned int j = 0; !del && j < _codes.size(); ++j)
        {
            if(_codes[j].getHitbox().intersects(_bugs[i].getHitbox()))
            {
                float angle = _bugs[i].angleTo(_codes[j]);
                angle = angle * 360 / (2 * 3.1415);

                if(angle > 315.f && angle < 45.f) _bugs[i].setVelocity(sf::Vector2f(-_bugs[i].getVelocity().x, _bugs[i].getVelocity().y));
                else if(angle > 45.f && angle < 135.f) _bugs[i].setVelocity(sf::Vector2f(_bugs[i].getVelocity().x, -_bugs[i].getVelocity().y));
                else if(angle > 135.f && angle < 225.f) _bugs[i].setVelocity(sf::Vector2f(-_bugs[i].getVelocity().x, _bugs[i].getVelocity().y));
                else if(angle > 225.f && angle < 315.f) _bugs[i].setVelocity(sf::Vector2f(_bugs[i].getVelocity().x, -_bugs[i].getVelocity().y));

                if(_codes[j].hit())
                {
                    _codes.erase(_codes.begin()+j);
                    _player.bugKilled();
                    del = true;
                }
            }
        }

        if(_bugs[i].getCenter().x > Game::_scrW || _bugs[i].getCenter().x < 0) _bugs[i].setVelocity(sf::Vector2f(-_bugs[i].getVelocity().x, _bugs[i].getVelocity().y));

        if(_bugs[i].getCenter().y > Game::_scrH || _bugs[i].getCenter().y < 0) _bugs[i].setVelocity(sf::Vector2f(_bugs[i].getVelocity().x, -_bugs[i].getVelocity().y));
    }
}

void Scene_Play::checkAttackKill()
{
    unsigned int bugsSize = _bugs.size();
    for(unsigned int i = 0; i < bugsSize; ++i)
    {
        if(_player.getAttackBounds().intersects(_bugs[i].getHitbox()))
        {
            int base = 10;
            if(_bugs.size() > 10) base -= 2;
            int rndInt = _rndGen.getRandInt(0, base + _player.getEnergy()/10);

            if(rndInt < 5)
            {
                _bugs.push_back(_bugs[i].cloneAndDivide());
            }
            else
            {
                _bugs.erase(_bugs.begin()+i);
                _player.addOneEnergy();
                _player.addOneEnergy();
            }
        }
    }
}