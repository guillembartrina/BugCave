#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <vector>
#include <iostream>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

struct Animation
{
    const sf::Texture* texture;
    std::vector<sf::IntRect> textureRects;
    sf::Time frameTime;
    bool repetition;
};

class AnimatedSprite : public sf::Sprite 
{
public:

    AnimatedSprite();
    ~AnimatedSprite();

    void addAnimation();
    void addAnimation(const sf::Texture& texture, unsigned int numFrames, sf::Vector2u size, const sf::Time& frameTime, bool repetition);
    void addAnimation(const sf::Texture& texture, unsigned int numFrames, unsigned int initRow, sf::Vector2u size, const sf::Time& frameTime, bool repetition);
    void addAnimation(const sf::Texture& texture, std::vector<sf::IntRect> frames, const sf::Time& frameTime, bool repetition);

    void setAnimationTexture(const sf::Texture& texture);

    void setAnimationFrameTime(const sf::Time& frameTime);

    void setAnimationFrames(unsigned int numFrames, sf::Vector2u size);
    void setAnimationFrames(unsigned int numFrames, unsigned int initRow, sf::Vector2u size);
    void setAnimationFrames(std::vector<sf::IntRect> frames);

    void setAnimationRepetition(bool repetition);

    void setActiveAnimation(unsigned int index, bool play = true);

    void playAnimation();

    void pauseAnimation();

    void stopAnimation();

    void firstFrame();

    void nextFrame();

    void setFrame(unsigned int frame);

    void updateAnimation(const sf::Time& deltatime);

    bool isAnimationPlaying();

    bool hasAnimationEnded();

private:

    std::vector<Animation> _animations;

    Animation* _currentAnimation;

    unsigned int _currentFrame;

    sf::Time _currentTime;

    bool _playing;

};

#endif