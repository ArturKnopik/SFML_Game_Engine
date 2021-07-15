#include "TestGameState.h"
#include "Player.h"
#include "KOD/ResourceManager.h"
#include "PlayerUpdatable.h"
#include "KOD/UtilityTools.h"
#include "KOD/ObjectManager.h"
#include <sstream>


void TestGameState::printTestMassage()
{
	KOD::sendDebugInformation("test text: " + std::string("sample text"));

	int randomInt1 = KOD::generateRandomIntNumber(1, 10);
	int randomInt2 = KOD::generateRandomIntNumber(10, 20);
	int randomInt3 = KOD::generateRandomIntNumber(20, 30);
	std::cout << "random int1:\n   " << randomInt1 << "\n   " << randomInt2 << "\n   " << randomInt3 << std::endl;
	double randomDouble1 = KOD::generateRandomDoubleNumber(1.0, 10.00);
	double randomDouble2 = KOD::generateRandomDoubleNumber(10.0, 20.00);
	double randomDouble3 = KOD::generateRandomDoubleNumber(20.0, 30.00);
	std::cout << "random double:\n   " << randomDouble1 << "\n   " << randomDouble2 << "\n   " << randomDouble3 << std::endl;
}

void TestGameState::checkCollision()
{
	/*
	  for (auto& iterObjA : m_localObjectMap)
	  {

		for (auto& iterObjB : m_localObjectMap)
		{
		  if (!compareObjectUid(iterObjA.second, iterObjB.second))
		  {
			auto solidObjectA = iterObjA.second->getSolid();
			auto solidObjectB = iterObjB.second->getSolid();
			if (KOD::collsionDetectionAABBObjByObj(iterObjA.second, iterObjB.second))
			{
			  iterObjA.second->getSolid()->onCollsion();
			  iterObjB.second->getSolid()->onCollsion();
			  //KOD::sendDebugInformation("colision: " + std::to_string(iterObjA.second->getUid()) +
			  //                          ":" + std::to_string(iterObjB.second->getUid()));
			}
		  }
		}
	  }
	  */
}

bool TestGameState::compareObjectUid(std::shared_ptr<KOD::IGameObject> left, std::shared_ptr<KOD::IGameObject> right)
{
	if (left == nullptr || right == nullptr)
	{
		return false;
	}
	if (left->getUid() == right->getUid())
	{
		return true;
	}
	return false;
}

TestGameState::TestGameState(std::shared_ptr<KOD::Game> game)
{
	m_game = game;
	sf::Vector2f extendLocalAreaSize = { 100, 100 };
	setAdditionalSpaceToSet(extendLocalAreaSize);
	// START: TESTING PIECE OF CODE

	printTestMassage();
	
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("resource\\playerSpaceShip.png");
	KOD::ResourceManager::getInstance().addResource("playerSpaceShip", texture);
	
	m_player = std::make_shared<Player>();
	m_player->setPosition({ 50, 50 });
	addGameObject(m_player);

	m_player2 = std::make_shared<Player>();
	m_player2->setPosition({ 100,100 });
	addGameObject(m_player2);
	
	m_player->getDrawable()->getAnimationController().play();
	sf::Vector2f playerPosition = { static_cast<float>(game->m_window.getSize().x / 2),
									static_cast<float>(game->m_window.getSize().y) - 150
	};
	//m_player->setPosition(playerPosition);
	// m_camera.bindGameObiect(m_player);
	 // END TESTING PIECE OF CODE
}

void TestGameState::input()
{
	IGameState::input();
	//TODO::find way to remove dynamic pointer casting


	std::shared_ptr<PlayerUpdatable> playerUpdatable;
	if (m_player && m_player->getUpdatable() != nullptr)
	{
		playerUpdatable = std::dynamic_pointer_cast<PlayerUpdatable>(m_player->getUpdatable());
		playerUpdatable->setHorizontalDirection(PlayerUpdatable::Direction::STOP);
		playerUpdatable->setVerticalDirection(PlayerUpdatable::Direction::STOP);
		// Some controll keys
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{	
			playerUpdatable->setVerticalDirection(PlayerUpdatable::Direction::UP);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			playerUpdatable->setVerticalDirection(PlayerUpdatable::Direction::DOWN);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			playerUpdatable->setHorizontalDirection(PlayerUpdatable::Direction::LEFT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			playerUpdatable->setHorizontalDirection(PlayerUpdatable::Direction::RIGHT);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			playerUpdatable->setHorizontalDirection(PlayerUpdatable::Direction::RIGHT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		{
			m_camera.setPosition({ 400,300 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		{
			m_camera.bindGameObiect(m_player);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
		{
			m_camera.bindGameObiect(m_player2);
		}
	}

	while (m_game.lock()->m_window.pollEvent(*m_event))
	{
		switch (m_event->type)
		{
		case sf::Event::Closed:
			m_game.lock()->m_window.close();
			break;

		case sf::Event::KeyPressed:
			if (m_event->key.code == sf::Keyboard::Escape)
			{
				// fast quit code
				m_game.lock()->m_window.close();
			}
			break;
		}
	}
}

void TestGameState::update(const size_t dt)
{
	IGameState::update(dt);
	checkCollision();
}


TestGameState::~TestGameState()
{
}
