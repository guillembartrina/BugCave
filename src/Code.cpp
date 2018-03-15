#include "Code.hpp"

RandomGenerator Code::_rnd = RandomGenerator();

const sf::Vector2f Code::_rectangleSize = sf::Vector2f(32.f, 32.f);
const int Code::_maxLife = 100;

Code::Code()
{
	setPosition(sf::Vector2f(0, 0));
	setSize(_rectangleSize);
}

Code::Code(const sf::Vector2f& position, const int energy)
{
	_life = _rnd.getRandInt(energy - 20, _maxLife - (_maxLife - energy));

	setPosition(sf::Vector2f(position.x * _rectangleSize.x, position.y * _rectangleSize.y));
	setSize(_rectangleSize);

	_code.setPosition(getPosition());
	_code.setSize(getSize());
	_code.setFillColor(sf::Color::Black);
	_code.setOutlineColor(sf::Color::Black);
	_code.setOutlineThickness(-2.f);
	_code.setFillColor(sf::Color(150, _life * 255/100, 0));

	_textCode.setFont(_resources.Font("font"));
	_textCode.setPosition(getPosition() + sf::Vector2f(5.f, 3.f));
   	_textCode.setString(std::to_string(_life));
	_textCode.setCharacterSize(16);
}

Code::~Code()
{
}

void Code::update()
{
	
}

void Code::draw(sf::RenderWindow& window) const
{
    window.draw(_code);
    window.draw(_textCode);
} 

bool Code::hit()
{
   --_life;
   _code.setFillColor(sf::Color(150, _life * 255/100, 0));
   _textCode.setString(std::to_string(_life));
   return (_life <= 0);  
}

const sf::Vector2f& Code::getWH()
{
  return _rectangleSize;
}
