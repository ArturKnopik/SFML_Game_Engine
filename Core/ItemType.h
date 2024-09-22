#pragma once
#include <ResourceManager.h>
#include <SFML/Graphics/Texture.hpp>
#include <cstdint>
#include <map>
#include <memory>
#include <string_view>

class ItemType;

class ItemTypeManager
{
public:
	void loadFromFile(std::string_view filename, kod::ResourceManager& resourceManager);
	void add(ItemType itemType);
	const ItemType& get(uint32_t id);

private:
	std::map<uint32_t, ItemType> m_itemTypes;
};

class ItemType
{
public:
	ItemType(uint32_t id);
	uint32_t getId();
	void setName(std::string_view name);
	std::string_view getName();
	bool isWalkable();
	void isWalkable(bool isWalkable);
	void setTexture(std::shared_ptr<sf::Texture> texture);

private:
	std::string m_name = "";
	bool m_isGround = false;
	bool m_isWalkable = false;
	uint32_t m_id;
	std::shared_ptr<sf::Texture> m_texture;
};
