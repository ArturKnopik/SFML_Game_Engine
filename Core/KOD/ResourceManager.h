#pragma once
#include "KOD_export.h"
#include "SFML/Graphics/Texture.hpp"
#include <memory>
#include <unordered_map>
#include <utility>
#include <string>
#include <iostream>
#include "ResourceHandler.h"

namespace KOD
{
	class KOD_API ResourceManager
	{
	private:
		ResourceHandler<sf::Texture> m_textureHandler;

		ResourceManager();
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) =delete;
		ResourceManager& operator=(const ResourceManager&)=delete;
		ResourceManager& operator=(ResourceManager&&) =delete;
	public:
		static ResourceManager & getInstance();
		~ResourceManager() 
		{
		};
		void addResource(std::string name, std::shared_ptr<sf::Texture>);
		//void addResource(std::shared_ptr< [SOUND OBJ] > sound, std::string name);
		std::shared_ptr<sf::Texture> getTexture(std::string name);
		void clean();
	};

}

