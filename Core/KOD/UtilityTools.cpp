#include "UtilityTools.h"

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
