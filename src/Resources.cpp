#include "Resources.hpp"

ResourceManager Resources::_resourceManager;

Resources::Resources() {}

Resources::~Resources() {}

void Resources::setResourcePath(const std::string& path)
{
	_resourceManager.setResourcePath(path);
}

const sf::Texture& Resources::Texture(const std::string& id)
{
	return _resourceManager.Texture(id);
}

const sf::Font& Resources::Font(const std::string& id)
{
	return _resourceManager.Font(id);
}

const sf::SoundBuffer& Resources::Sound(const std::string& id)
{
	return _resourceManager.Sound(id);
}

sf::Music& Resources::Music(const std::string& id)
{
	return _resourceManager.Music(id);
}

void Resources::clearTextures()
{
	_resourceManager.clearTextures();
}

void Resources::clearFonts()
{
	_resourceManager.clearFonts();
}

void Resources::clearSounds()
{
	_resourceManager.clearSounds();
}

void Resources::clearMusics()
{
	_resourceManager.clearMusics();
}