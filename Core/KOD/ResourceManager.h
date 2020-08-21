#pragma once
#include "KOD_export.h"
#include "SFML/Graphics/Texture.hpp"
#include <memory>
#include <unordered_map>
#include <utility>
#include <string>

namespace KOD
{
	class KOD_API ResourceManager
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textureList;
		//std::unordered_map<std::string, std::shared_ptr<[SOUND OBJ]>> m_soundList; 
		ResourceManager();
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) =delete;
		ResourceManager& operator=(const ResourceManager&)=delete;
		ResourceManager& operator=(ResourceManager&&) =delete;
	public:
		static ResourceManager & getInstance();
		~ResourceManager()=default;
		const std::unordered_map<std::string, std::shared_ptr<sf::Texture>>& getTextureList() const;
		void addResource(std::string name, std::shared_ptr<sf::Texture> texture);
		//void addResource(std::shared_ptr< [SOUND OBJ] > sound, std::string name);
		std::shared_ptr<sf::Texture> getTexture(std::string name);
	};

}

