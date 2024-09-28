#include "ResourceManager.h"

#include <iostream>

void kod::ResourceManager::addResource(std::string_view name, std::shared_ptr<sf::Texture> texture)
{
	this->m_textureHandler.add(name, texture);
}

void kod::ResourceManager::addResource(std::string_view name, kod::Animation animation)
{
	m_animationHandler.add(name, std::move(animation));
}

void kod::ResourceManager::addResource(std::string_view name, sf::Font font) {
	m_fontHandler.add(name, std::move(font));
}

std::shared_ptr<sf::Texture> kod::ResourceManager::getTexture(std::string_view name)
{
	if (m_textureHandler.get(name))
	{
		return *m_textureHandler.get(name);
	}
	return nullptr;
}

kod::Animation* kod::ResourceManager::getAnimation(std::string_view name) { return m_animationHandler.get(name); }

sf::Font* kod::ResourceManager::getFont(std::string_view name)
{ return m_fontHandler.get(name); }

void kod::ResourceManager::clean()
{
	m_textureHandler.clean();
	m_animationHandler.clean();
	m_fontHandler.clean();
}