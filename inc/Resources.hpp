#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "ResourceManager.hpp"

class Resources {
public:
    Resources();

    ~Resources();

    void setResourcePath(const std::string& path);

    const sf::Texture& Texture(const std::string& id);

    const sf::Font& Font(const std::string& id);

    const sf::SoundBuffer& Sound(const std::string& id);
	
    sf::Music& Music(const std::string& id);

    void clearTextures();

    void clearFonts();

    void clearSounds();

    void clearMusics();

private:

    static ResourceManager _resourceManager;

};

#endif