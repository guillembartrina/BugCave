#ifndef SCENE__PLAY_HPP
#define SCENE__PLAY_HPP

#include <vector>

#include "Scene.hpp"
#include "Resources.hpp"
#include "Player.hpp"
#include "Code.hpp"
#include "Bug.hpp"
#include "RandomGenerator.hpp"

class Scene_Play : public Scene
{
public:

    Scene_Play(SceneManager& sceneManager);
    ~Scene_Play();

    void init();

    void handleEvents(const sf::Event& event);

    void update(const sf::Time deltatime);

    void draw(sf::RenderWindow& window) const;

    void pause();

    void resume();

    void addRndBug(bool add, int prob);

    void handleBugs(const sf::Time deltatime);

    void checkAttackKill();

private:

    RandomGenerator _rndGen;

    Resources _resources;

    Player _player;

    std::vector<Code> _codes;
    std::vector< std::vector<bool> > _codeMap;

    std::vector<Bug> _bugs;

    const int _scoreMax = 20;
    int _score;

    sf::Sprite _spriteBackground;

    sf::Text _textRedbull;
    sf::Text _textScore;
    sf::Text _textEnergy;

    int _touching;

    const sf::Time _nextEnergy = sf::seconds(1.f);
    sf::Time _currentTime;

};

#endif
