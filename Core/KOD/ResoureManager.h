#pragma once
#include <unordered_map>
#include <memory>
#include "TibiaResourceHandler.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Audio/Sound.hpp"
namespace TCG
{
	class ResoureManager
	{
		TGC::ResourceHandler<sf::Texture> textureHandler;
		TGC::ResourceHandler<sf::Sound> soundHandler;
		ResoureManager() = default;
		ResoureManager(ResoureManager&&) = delete;
		ResoureManager(ResoureManager&) = delete;
	public:
		~ResoureManager() = default;
		static ResoureManager& getInstance();
		TGC::ResourceHandler<sf::Texture>& getTextureHandler();
		TGC::ResourceHandler<sf::Sound>& getSoundHandler();
	};
}

