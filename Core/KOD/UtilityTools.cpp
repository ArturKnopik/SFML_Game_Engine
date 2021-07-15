#include "UtilityTools.h"
#include "SFML/Graphics/RectangleShape.hpp"

void KOD_API KOD::sendDebugInformation(std::string message)
{
	if (debugMode == true)
	{
		std::cout << message << std::endl;
	}
}

int KOD_API KOD::generateRandomIntNumber(int min, int max)
{
	static std::random_device randomDevice;
	static std::default_random_engine randomEngine(randomDevice());
	std::uniform_int_distribution<int> uniform_dist(min, max);
	return uniform_dist(randomEngine);
}

double KOD_API KOD::generateRandomDoubleNumber(double min, double max)
{
	static std::random_device randomDevice;
	static std::default_random_engine randomEngine(randomDevice());
	std::uniform_real_distribution<double> uniform_dist(min, max);
	return uniform_dist(randomEngine);
}

float KOD_API KOD::generateRandomFloatNumber(float min, float max)
{
	static std::random_device randomDevice;
	static std::default_random_engine randomEngine(randomDevice());
	std::uniform_real_distribution<float> uniform_dist(min, max);
	return uniform_dist(randomEngine);
}

bool KOD_API KOD::collsionDetectionAABBObjByObj(IGameObject_prt left, IGameObject_prt right)
{
	if (left->getCollider() == nullptr || right->getCollider() == nullptr)
	{
		return false;
	}
	for (const auto& leftSingleRectCollider : left->getCollider()->getColliders())
	{
		for (const auto& rightSingleRectCollider : right->getCollider()->getColliders())
		{

			sf::Vector2f positionLeft = left->getPosition() + leftSingleRectCollider.first;
			sf::Vector2f positionRight = right->getPosition() + rightSingleRectCollider.first;
			sf::Vector2f sizeLeft = leftSingleRectCollider.second;
			sf::Vector2f sizeRight = rightSingleRectCollider.second;
			if (collsionDetectionAABBPosByPos(positionLeft, sizeLeft, positionRight, sizeRight))
			{
				return true;
			}
		}
	}

	return false;
}

bool KOD_API KOD::collsionDetectionAABBPosByPos(sf::Vector2f posizeLeft, sf::Vector2f sizeLeft, sf::Vector2f posizeRight, sf::Vector2f sizeRight)
{
	if (posizeLeft.x <= posizeRight.x + sizeRight.x &&
		posizeLeft.x + sizeLeft.x >= posizeRight.x &&
		posizeLeft.y <= posizeRight.y + sizeRight.y &&
		sizeLeft.y + posizeLeft.y >= posizeRight.y)
	{
		return true;
	}
	return false;
}

std::string KOD_API KOD::clearScreen(std::string cleanInfo)
{
#ifdef _WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif
	system(CLEAR);
	return cleanInfo;
}
