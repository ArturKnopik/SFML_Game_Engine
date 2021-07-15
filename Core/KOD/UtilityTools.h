#pragma once
#include "KOD_export.h"
#include "Settings.h"
#include "KOD/IGameObject.h"
#include "SFML/System/Vector2.hpp"
#include <random>

namespace KOD {
  void KOD_API sendDebugInformation(std::string message);

  int KOD_API generateRandomIntNumber(int min, int max);

  double KOD_API generateRandomDoubleNumber(double min, double max);

  float KOD_API generateRandomFloatNumber(float min, float max);

  bool KOD_API collsionDetectionAABBObjByObj(IGameObject_prt left, IGameObject_prt right);

  bool KOD_API collsionDetectionAABBPosByPos(sf::Vector2f posLeft, sf::Vector2f sizeLeft, sf::Vector2f posRight, sf::Vector2f sizeRight);


  std::string KOD_API clearScreen(std::string cleanInfo);
 
}