
#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite() : sf::Sprite()
{
    _currentAnimation = nullptr;
    _currentFrame = 0;
    _currentTime = sf::Time::Zero;
    _playing = false;
}

AnimatedSprite::~AnimatedSprite()
{
    _animations.clear();
}

void AnimatedSprite::addAnimation()
{
    Animation animation;
    _animations.push_back(animation);
}

void AnimatedSprite::addAnimation(const sf::Texture& texture, unsigned int numFrames, sf::Vector2u size, const sf::Time& frameTime, bool repetition)
{
    _animations.push_back(Animation());

    _currentAnimation = &_animations.back();

    setAnimationTexture(texture);
    setAnimationFrames(numFrames, size);
    setAnimationFrameTime(frameTime);
    setAnimationRepetition(repetition);

    _currentAnimation = nullptr;

}

void AnimatedSprite::addAnimation(const sf::Texture& texture, unsigned int numFrames, unsigned int initRow, sf::Vector2u size, const sf::Time& frameTime, bool repetition)
{
    _animations.push_back(Animation());

    _currentAnimation = &_animations.back();

    setAnimationTexture(texture);
    setAnimationFrames(numFrames, initRow, size);
    setAnimationFrameTime(frameTime);
    setAnimationRepetition(repetition);

    _currentAnimation = nullptr;

}

void AnimatedSprite::addAnimation(const sf::Texture& texture, std::vector<sf::IntRect> frames, const sf::Time& frameTime, bool repetition)
{

    _animations.push_back(Animation());

    _currentAnimation = &_animations.back();

    setAnimationTexture(texture);
    setAnimationFrames(frames);
    setAnimationFrameTime(frameTime);
    setAnimationRepetition(repetition);

    _currentAnimation = nullptr;
}

void AnimatedSprite::setAnimationTexture(const sf::Texture& texture)
{
    if(_currentAnimation != nullptr)
    {
        _currentAnimation->texture = &texture;
    }
}

void AnimatedSprite::setAnimationFrameTime(const sf::Time& frameTime)
{
    if(_currentAnimation != nullptr)
    {
        _currentAnimation->frameTime = frameTime;
    }
}

void AnimatedSprite::setAnimationFrames(unsigned int numFrames, sf::Vector2u size)
{
    if(_currentAnimation != nullptr)
    {
        for(unsigned int i = 0; i < numFrames; ++i)
        {
            unsigned int textureW = _currentAnimation->texture->getSize().x;
            int posX = (i * size.x) % (textureW);
            int posY = int((i * size.x) / (textureW));
            _currentAnimation->textureRects.push_back(sf::IntRect(posX, posY, size.x, size.y));
        }
    }
}

void AnimatedSprite::setAnimationFrames(unsigned int numFrames, unsigned int initRow, sf::Vector2u size)
{
    if(_currentAnimation != nullptr)
    {
        for(unsigned int i = 0; i < numFrames; ++i)
        {
            unsigned int textureW = _currentAnimation->texture->getSize().x;
            int posX = (i * size.x) % (textureW);
            int posY = (initRow * size.y) + int((i * size.x) / (textureW));
            _currentAnimation->textureRects.push_back(sf::IntRect(posX, posY, size.x, size.y));
        }
    }
}

void AnimatedSprite::setAnimationFrames(std::vector<sf::IntRect> frames)
{
    if(_currentAnimation != nullptr)
    {
        _currentAnimation->textureRects = frames;
    }
}

void AnimatedSprite::setAnimationRepetition(bool repetition)
{
    if(_currentAnimation != nullptr)
    {
        _currentAnimation->repetition = repetition;
    }
}

void AnimatedSprite::setActiveAnimation(unsigned int index, bool play)
{
    if(!_animations.empty() && index < _animations.size())
    {
        _currentAnimation = &_animations[index];
        setTexture(*_currentAnimation->texture);
        _currentTime = sf::Time::Zero;
        _playing = play;
        firstFrame();
    }
    else
    {
        std::cerr << "No animation of index <" << index <<">." << std::endl;
    }
}

void AnimatedSprite::playAnimation()
{
    _playing = true;
}

void AnimatedSprite::pauseAnimation()
{
    _playing = false;
}

void AnimatedSprite::stopAnimation()
{
    firstFrame();
    _playing = false;
}

void AnimatedSprite::firstFrame()
{
    if(_currentAnimation != nullptr)
    {
        if(!_currentAnimation->textureRects.empty())
        {
            _currentFrame = 0;
            setTextureRect(_currentAnimation->textureRects[_currentFrame]);
        }
    }
}

void AnimatedSprite::nextFrame()
{
    if(_currentAnimation != nullptr)
    {
        if(!_currentAnimation->textureRects.empty())
        {
            if((_currentAnimation->repetition) || !(_currentFrame == _currentAnimation->textureRects.size()-1))
            {
                _currentFrame = (_currentFrame + 1) % _currentAnimation->textureRects.size();
            }
            setTextureRect(_currentAnimation->textureRects[_currentFrame]);
        }
    }
}

void AnimatedSprite::setFrame(unsigned int frame)
{
    if(_currentAnimation != nullptr)
    {
        if(!_currentAnimation->textureRects.empty() && frame < _currentAnimation->textureRects.size())
        {
            _currentFrame = frame;
            setTextureRect(_currentAnimation->textureRects[_currentFrame]);
        }
        else
        {
            std::cerr << "No frame of index <" << frame << ">." << std::endl;
        }
    }
}

void AnimatedSprite::updateAnimation(const sf::Time& deltatime)
{
    if(_currentAnimation != nullptr)
    {
        if(_playing)
        {
            _currentTime += deltatime;
            if(_currentTime >= _currentAnimation->frameTime)
            {
                nextFrame();
                _currentTime -= _currentAnimation->frameTime;
            }
        }
    }
}

bool AnimatedSprite::isAnimationPlaying()
{
    return _playing;
}

bool AnimatedSprite::hasAnimationEnded()
{
    if(_currentAnimation != nullptr)
    {
        if((!_currentAnimation->repetition) && (_currentFrame == _currentAnimation->textureRects.size()-1))
        {
            return true;
        }
    }
    
    return false;
}