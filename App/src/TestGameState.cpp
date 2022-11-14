#include "TestGameState.h"
#include "Player.h"
#include "KOD/ResourceManager.h"
#include "PlayerUpdatable.h"
#include "KOD/UtilityTools.h"
#include <sstream>


void TestGameState::printTestMassage()
{
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

/*
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
*/

TestGameState::TestGameState(std::shared_ptr<KOD::Game> game)
	:IState(game), World(KOD::BoundingBox{ {0,0}, {800, 600} })
{
	// START: TESTING PIECE OF CODE

	printTestMassage();
	
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("resource\\playerSpaceShip.png");
	KOD::ResourceManager::getInstance().addResource("playerSpaceShip", texture);
	
	m_player = std::make_shared<Player>();
	m_player->setPosition({ 100, 100 });
	addGameObject(m_player);
	auto player2 = std::make_shared<Player>();
	player2->setPosition({200,100});
	addGameObject(player2);
	player2 = std::make_shared<Player>();
	player2->setPosition({100,200});
	addGameObject(player2);
	player2 = std::make_shared<Player>();
	player2->setPosition({ 200,200 });
	addGameObject(player2);	player2 = std::make_shared<Player>();
	player2->setPosition({ 150,150 });
	addGameObject(player2);
	//addGameObject(std::make_shared<Player>());
	//addGameObject(std::make_shared<Player>());
	//addGameObject(std::make_shared<Player>());
	//addGameObject(std::make_shared<Player>());
	for (auto& obj : getObjectList())
	{
	//	m_qTree.addGameObject(obj.second);
	}
	 // END TESTING PIECE OF CODE
	std::cout << getObjectList().size() << std::endl;
	addGameObject(m_player);
}

void TestGameState::draw()
{
	sf::RenderWindow& rw = m_game.lock()->getRenderWindow();
	for (auto& it : getObjectList()) 
	{
		it.second->draw(rw);
	}
	m_qTree.drawQT(rw);
	std::cout << "DRAW END" << std::endl;
}

void TestGameState::update(const size_t dt)
{
	g_dt = dt;
	m_qTree.clear();
	m_player->getFlags();
	for (auto& it : getObjectList()) 
	{
		m_qTree.addGameObject(it.second);
		it.second->update(dt);
	}
}

void TestGameState::input()
{
	while (m_game.lock()->getRenderWindow().pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_game.lock()->getRenderWindow().close();
			break;

		case sf::Event::KeyPressed:
			if (m_event.key.code == sf::Keyboard::Escape)
			{
				// fast quit code
				m_game.lock()->getRenderWindow().close();
			}
			break;
		}
	}
}

TestGameState::~TestGameState()
{
}
