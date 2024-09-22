#pragma once
#include "Animation.h"
#include "ResourceHandler.h"
#include "SFML/Graphics/Texture.hpp"
#include "export.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace kod {
class ResourceManager
{
public:
	KOD_API ResourceManager() = default;
	KOD_API ~ResourceManager() = default;
	KOD_API void addResource(std::string_view name, std::shared_ptr<sf::Texture> texture);
	KOD_API void addResource(std::string_view name, kod::Animation animation);
	KOD_API std::shared_ptr<sf::Texture> getTexture(std::string_view name);
	KOD_API kod::Animation* getAnimation(std::string_view name);
	KOD_API void clean();

private:
	ResourceHandler<std::shared_ptr<sf::Texture>> m_textureHandler;
	ResourceHandler<kod::Animation> m_animationHandler;
	// TODO: sounds, fonts, etc..

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
};

} // namespace kod
