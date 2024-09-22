#include "ItemType.h"

#include "Logger.h"

#include <Game.h>
#include <Json.h>
#include <iostream>

ItemType::ItemType(uint32_t id) : m_id(id) {}

uint32_t ItemType::getId() { return m_id; }

void ItemType::setName(std::string_view name) { m_name = std::string(name); }

std::string_view ItemType::getName() { return std::string_view(m_name); }

bool ItemType::isWalkable() { return m_isWalkable; }

void ItemType::isWalkable(bool isWalkable) { m_isWalkable = isWalkable; }

void ItemType::setTexture(std::shared_ptr<sf::Texture> texture)
{
	if (!texture) {
		g_logger.log(
		    kod::Logger::LogSeverity::ERROR,
		    std::string("ItemType with id " + std::to_string(getId()) + " is trying to set invalid texture").c_str());
		return;
	}

	m_texture = texture;
}

void ItemTypeManager::loadFromFile(std::string_view filename, kod::ResourceManager& resourceManager)
{
	// TODO: load from json file
	g_logger.log(kod::Logger::LogSeverity::ERROR, std::string("STUB implementation").c_str());
	std::ifstream f("./Assets/Json/ItemType.json");
	if (f.is_open()) {
		g_logger.log(kod::Logger::LogSeverity::ERROR, "Opening file");
		try {
			using json = nlohmann::json;
			json data = json::parse(f);
			if (!data.contains("ItemTypes")) {
				g_logger.log(kod::Logger::LogSeverity::ERROR, "Fail to find ItemType array");
				return;
			}
			auto arr = data["ItemTypes"];
			for (auto& jit : arr) {
				if (!jit.contains("id") or !jit.contains("texture")) {
					g_logger.log(kod::Logger::LogSeverity::ERROR, "Fail to 'id' or 'texture' node");
					continue;
				}
				auto it = ItemType(jit["id"]);
				auto texture = resourceManager.getTexture(std::string_view(jit["texture"]));
				if (!texture) {
					g_logger.log(kod::Logger::LogSeverity::ERROR,
					             std::string("invalid texturec for ItemType with  ID: " + std::to_string(it.getId())).c_str());
					continue;
				}
				it.setTexture(texture);
				if (jit.contains("isWalkable")) {
					it.isWalkable(jit["isWalkable"]);
				}
				add(it);
				g_logger.log(kod::Logger::LogSeverity::DEBUG,
				             std::string("ItemType " + std::to_string(it.getId()) + " added").c_str());
			}
		} catch (const std::exception& e) {
			g_logger.log(kod::Logger::LogSeverity::ERROR, e.what());
		}
	}
}

void ItemTypeManager::add(ItemType itemType)
{
	uint32_t itemId = itemType.getId(); // for logger

	if (!m_itemTypes.emplace(itemType.getId(), std::move(itemType)).second) {
		g_logger.log(kod::Logger::LogSeverity::ERROR,
		             std::string("ItemType with id " + std::to_string(itemId) + " already exist").c_str());
	}
}

const ItemType& ItemTypeManager::get(uint32_t id) { return m_itemTypes.at(id); }
