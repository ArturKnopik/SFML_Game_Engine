#include "ResourceManager.h"

#include "UtilityTools.h"

#include <iostream>

KOD::ResourceManager::ResourceManager() {}

KOD::ResourceManager& KOD::ResourceManager::getInstance()
{
	static ResourceManager s;
	return s;
}

void KOD::ResourceManager::addResource(std::string name, std::shared_ptr<sf::Texture> texture)
{
	this->m_textureHandler.addResource(name, texture);
}

std::shared_ptr<sf::Texture> KOD::ResourceManager::getTexture(std::string name)
{
	return m_textureHandler.getResourceByName(name);
}

void KOD::ResourceManager::clean() { m_textureHandler.clean(); }