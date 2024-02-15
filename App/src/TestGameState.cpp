#include "TestGameState.h"

#include "KOD/ResourceManager.h"
#include "KOD/UtilityTools.h"
#include "Player.h"
#include "PlayerUpdatable.h"

#include <chrono>
#include <sstream>

void TestGameState::printTestMassage() {}

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

TestGameState::TestGameState(std::shared_ptr<KOD::Game> game) :
    IState(game), World(KOD::BoundingBox{{0, 0}, {800, 600}})
{
	// START: TESTING PIECE OF CODE

	printTestMassage();

	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("resource\\playerSpaceShip.png");
	KOD::ResourceManager::getInstance().addResource("playerSpaceShip", texture);

	m_player = std::make_shared<Player>();
	m_player->setPosition({1, 1});
	addGameObject(m_player);

	for (auto& it : getObjectList()) {
		m_qTree.addGameObject(it.second);
		;
	}
}

void TestGameState::draw()
{
	sf::RenderWindow& rw = m_game.lock()->getRenderWindow();
	for (auto& it : getObjectList()) {
		it.second->draw(rw);
	}
	m_qTree.drawQT(rw);
}

void TestGameState::update(const size_t dt)
{
	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
	g_dt = dt;

	m_qTree.clear();

	for (auto& it : getObjectList()) {
		it.second->update(dt);
		m_qTree.addGameObject(it.second);
	}
	KOD::BoundingBox bb;
	bb.m_position = {1, 1};
	bb.m_size = {398, 298};
	/*
	std::cout << "------ ===== Quad Tree tests ===== ------" <<
	    "\n\tgame obj size: " << getObjectList().size() <<
	    "\n\tqTree obj size(all nodes): " << m_qTree.getObjectCount() <<
	    "\n\tqtree all nodes count: " << m_qTree.getAllNodes().size() <<
	    "\n\tqTree nodecount(from pos: " << bb.m_position.x << ":" << bb.m_position.y << ", size:  " << bb.m_size.x <<
	":" << bb.m_size.y << "): " << m_qTree.getNodesInArea(bb).size() << std::endl;
	    */
	std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> frameTime;

	frameTime = endTime - startTime;
	auto fps = 1.0 / frameTime.count();
	std::stringstream stream;
	stream << "FPS : " << static_cast<uint32_t>(fps) << " |  obj: " << m_qTree.getObjectCount();
	m_game.lock()->getRenderWindow().setTitle(stream.str());
}

void TestGameState::input()
{
	while (m_game.lock()->getRenderWindow().pollEvent(m_event)) {
		switch (m_event.type) {
			case sf::Event::Closed:
				m_game.lock()->getRenderWindow().close();
				break;

			case sf::Event::KeyPressed:
				if (m_event.key.code == sf::Keyboard::Escape) {
					// fast quit code
					m_game.lock()->getRenderWindow().close();
				}

				if (m_event.key.code == sf::Keyboard::R) {
					for (size_t i = 0; i < 50; i++) {
						m_player = std::make_shared<Player>();
						m_player->setPosition(
						    {KOD::generateRandomFloatNumber(0, 800), KOD::generateRandomFloatNumber(0, 600)});
						addGameObject(m_player);
					}
				}
				if (m_event.key.code == sf::Keyboard::W) {
					m_player = std::make_shared<Player>();
					m_player->setPosition({10, 10});
					addGameObject(m_player);
				}
				break;
		}
	}
}

TestGameState::~TestGameState() {}
