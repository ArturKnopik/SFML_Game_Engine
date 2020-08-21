#include "ResourceManager.h"
#include "UtilityTools.h"
#include <iostream>

KOD::ResourceManager::ResourceManager()
{
}

KOD::ResourceManager& KOD::ResourceManager::getInstance()
{
  static ResourceManager s;
  return s;
}

const std::unordered_map<std::string, std::shared_ptr<sf::Texture>>& KOD::ResourceManager::getTextureList() const
{
  return m_textureList;
}

void KOD::ResourceManager::addResource(std::string name, std::shared_ptr<sf::Texture> texture)
{
  for (auto it = m_textureList.begin(); it != m_textureList.end(); it++)
  {
    if (it->first == name)
    {
      if (KOD::debugMode)
      {
        std::cout << "error, texture named '" + name + "' exist in list" << std::endl;
      }
      return;
    }
  }
  m_textureList.insert({ name, texture });
  if (KOD::debugMode)
  {
    std::cout << "Added '" + name + "' to list" << std::endl;
  }
}

std::shared_ptr<sf::Texture> KOD::ResourceManager::getTexture(std::string name)
{
  for (auto it = m_textureList.begin(); it != m_textureList.end(); it++)
  {
    if (it->first == name)
    {
      return it->second;
    }
  }
  if (KOD::debugMode)
  {
    std::cout << "returned nullptr" << std::endl;
  }
  return nullptr;
}


