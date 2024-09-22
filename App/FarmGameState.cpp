#include "FarmGameState.h"

#include <Game.h>
#include <Json.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <random>
#include <string_view>

FarmGameState::FarmGameState(kod::Game& game) : IState(game)
{
	m_particleEmiter = kod::ParticleEmiter<SampleParticle>(10000);
	m_particleEmiter.setTimeBetweenParticleSpawn(200000);
	m_particleEmiter.setTimeBetweenParticleSpawn(5000);
	m_particleEmiter.maxSpawnedParticleAtOnce(10);
	m_particleEmiter.setPosition({750, 700});

	loadResources();
}

void FarmGameState::draw()
{
	auto c = sf::CircleShape();
	c.setFillColor(sf::Color::Red);
	c.setPosition({100, 100});
	c.setRadius(40);
	// m_game.getRenderWindow().draw(m_sprite1);
	// m_game.getRenderWindow().draw(c);

	m_sprite2.setColor(sf::Color(255, 255, 100, 100));
	m_sprite2.setPosition({300, 300});
	auto anim = m_game.getResourceManager().getAnimation("test");
	if (anim) {
		auto texture = anim->getCurrentFrame().getTexture();
		if (texture) {
			m_sprite2.setTextureRect(anim->getCurrentFrame().getFrameRect());
			m_sprite2.setTexture(*anim->getCurrentFrame().getTexture());
		}
	}
	// m_game.getRenderWindow().draw(m_sprite2);
	m_particleEmiter.draw(m_game.getRenderWindow());
}

void FarmGameState::update(const size_t dt)
{
	auto anim = m_game.getResourceManager().getAnimation("test");
	if (anim) {
		anim->update(dt);
	}

	m_particleEmiter.update(dt);

	sf::Time currentTime = m_clock.restart();
	float elapsed = currentTime.asSeconds();
	size_t m_fps = 0;

	m_game.getRenderWindow().setTitle("FPS: " + std::to_string(static_cast<size_t>(1.0 / elapsed)) +
	                                  ", particles: " + std::to_string(m_particleEmiter.getParticleCount()));
}

void FarmGameState::loadResources()
{
	g_logger.log(kod::Logger::LogSeverity::DEBUG, ">> Loading textures");
	loadTextures();
	auto texture = std::make_shared<sf::Texture>();
	if (texture->loadFromFile("./Assets/Images/terrain.png", {0, 0, 200, 200})) {
		m_game.getResourceManager().addResource("ground_grass_1", texture);
	}

	m_sprite1.setPosition({0, 0});
	m_sprite1.setTexture(*m_game.getResourceManager().getTexture("ground_grass_1"));

	g_logger.log(kod::Logger::LogSeverity::DEBUG, ">> Loading ItemTypes");
	m_itemTypeManager.loadFromFile("./Assets/Json/ItemType.json", m_game.getResourceManager());
	if (m_game.getResourceManager().getTexture("ground_grass_1")) {
		kod::Frame frame1({0, 0, 32, 32}, 1000);
		kod::Frame frame2({32, 0, 32, 32}, 1000);
		kod::Frame frame3({64, 0, 32, 32}, 1000);
		kod::Frame frame4({96, 0, 32, 32}, 1000);
		kod::Animation animation;
		frame1.setTexture(m_game.getResourceManager().getTexture("ground_grass_1"));
		frame2.setTexture(m_game.getResourceManager().getTexture("ground_grass_1"));
		frame3.setTexture(m_game.getResourceManager().getTexture("ground_grass_1"));
		frame4.setTexture(m_game.getResourceManager().getTexture("ground_grass_1"));
		animation.addFrame(frame1);
		animation.addFrame(frame2);
		animation.addFrame(frame3);
		animation.addFrame(frame4);
		m_game.getResourceManager().addResource("test", animation);
	}
}

void FarmGameState::loadTextures()
{
	g_logger.log(kod::Logger::LogSeverity::ERROR, "00 Fail to find 'textures' array");
	std::ifstream f("./Assets/Json/Textures.json");
	if (f.is_open()) {
		try {
			using json = nlohmann::json;
			json data = json::parse(f);
			if (!data.contains("textures")) {
				return;
			}
			auto txs = data["textures"];
			for (auto& tx : txs) {
				if (!tx.contains("file") or !tx.contains("name") or !tx.contains("width") or !tx.contains("height")) {
					g_logger.log(kod::Logger::LogSeverity::ERROR,
					             "Fail to 'file' or 'name' or 'width' or 'height' node");
					continue;
				}
				auto texture = std::make_shared<sf::Texture>();
				if (texture->loadFromFile(tx["file"], {0, 0, tx["width"], tx["height"]})) {
					m_game.getResourceManager().addResource(std::string_view(tx["name"]), texture);
					g_logger.log(kod::Logger::LogSeverity::DEBUG,
					             std::string("Texture '" + std::string(tx["name"]) + "' added").c_str());
				}
			}
		} catch (const std::exception& e) {
			g_logger.log(kod::Logger::LogSeverity::ERROR, e.what());
		}
	}
}

void FarmGameState::loadMaps() {}

void FarmGameState::switchCurrentMap(std::string_view mapName)
{
	auto map = std::find_if(
	    m_maps.begin(), m_maps.end(),
	    [mapName](const std::pair<std::string, std::shared_ptr<Map>>& element) { return element.first == mapName; });
	if (map != m_maps.end()) {
		m_currentMap = map->second;
	}
}