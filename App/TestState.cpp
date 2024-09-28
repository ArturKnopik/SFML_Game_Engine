#include "TestState.h"

#include <Game.h>
#include <Json.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <random>
#include <string_view>

TestState::TestState(kod::Game& game) : IState(game)
{
	m_particleEmiter = kod::ParticleEmiter<SampleParticle>(10000);
	m_particleEmiter.setTimeBetweenParticleSpawn(200000);
	m_particleEmiter.setTimeBetweenParticleSpawn(5000);
	m_particleEmiter.maxSpawnedParticleAtOnce(10);
	m_particleEmiter.setPosition({750, 700});

	auto font = sf::Font();
	font.loadFromFile("./Assets/Fonts/Arial.ttf");

	auto button = std::make_shared<kod::Button>("TTTTT");
	button->setFont(font);
	button->setPosition({100, 100});
	button->setSize({50, 20});
	button->setOutlineColorOnHover(sf::Color::Red);
	kod::ButtonCb buttonCb = [this]() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> x(300, 1200.f);
		std::uniform_real_distribution<float> y(600.f, 850.f);
		m_particleEmiter.setPosition({x(gen), y(gen)});
		std::cout << "Button was clicked!" << std::endl;
		
	};
	button->setCallback(buttonCb);
	addGuiElement(button);

	auto label = std::make_shared<kod::Label>("Test label");
	label->setFont(font);
	label->setString("text STR");
	label->setTextColor(sf::Color::Yellow);
	addGuiElement(label);

	loadResources();
}

void TestState::draw()
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

void TestState::update(const size_t dt)
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

void TestState::input(sf::Event& event) { }

void TestState::loadResources()
{
	g_logger.log(kod::Logger::LogSeverity::DEBUG, ">> Loading fonts");
	loadFonts();
	g_logger.log(kod::Logger::LogSeverity::DEBUG, ">> Loading textures");
	loadTextures();
	auto texture = std::make_shared<sf::Texture>();
	if (texture->loadFromFile("./Assets/Images/terrain.png", {0, 0, 200, 200})) {
		m_game.getResourceManager().addResource("ground_grass_1", texture);
	}

	m_sprite1.setPosition({0, 0});
	m_sprite1.setTexture(*m_game.getResourceManager().getTexture("ground_grass_1"));

	g_logger.log(kod::Logger::LogSeverity::DEBUG, ">> Loading ItemTypes");
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

void TestState::loadTextures()
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

void TestState::loadFonts()
{
	g_logger.log(kod::Logger::LogSeverity::ERROR, "00 Fail to find 'textures' array");
	std::ifstream f("./Assets/Json/Fonts.json");
	if (f.is_open()) {
		try {
			using json = nlohmann::json;
			json data = json::parse(f);
			if (!data.contains("fonts")) {
				return;
			}
			auto txs = data["fonts"];
			for (auto& tx : txs) {
				if (!tx.contains("file") or !tx.contains("name")) {
					g_logger.log(kod::Logger::LogSeverity::ERROR,
					             "Fail to 'file' or 'name' or 'width' or 'height' node");
					continue;
				}

				sf::Font font;
				if (font.loadFromFile(tx["file"])) {
					m_game.getResourceManager().addResource(std::string_view(tx["name"]), font);
					g_logger.log(kod::Logger::LogSeverity::DEBUG,
					             std::string("Texture '" + std::string(tx["name"]) + "' added").c_str());
				}
			}
		} catch (const std::exception& e) {
			g_logger.log(kod::Logger::LogSeverity::ERROR, e.what());
		}
	}
}