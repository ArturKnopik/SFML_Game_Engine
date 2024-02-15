#pragma once
#include "KOD_export.h"
#include "ResourceHandler.h"
#include "SFML/Graphics/Texture.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace KOD {
class KOD_API ResourceManager
{
private:
	ResourceHandler<sf::Texture> m_textureHandler;

	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

public:
	static ResourceManager& getInstance();
	~ResourceManager() = default;
	void addResource(std::string name, std::shared_ptr<sf::Texture>);
	std::shared_ptr<sf::Texture> getTexture(std::string name);
	void clean();
};

} // namespace KOD
