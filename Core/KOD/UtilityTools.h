#pragma once
#include "KOD_export.h"
#include "Settings.h"
#include <random>
namespace KOD {
  extern "C" {
    /*
    KOD_API void sendDebugInformation(std::string message)
    {
      if (debugMode == true)
      {
        std::cout << message << std::endl;
      }
    }

    KOD_API int generateRandomIntNumber(int min, int max)
    {
      static std::random_device randomDevice;
      static std::default_random_engine randEng(randomDevice());
      static std::uniform_int_distribution<int> uniform_dist(min, max);
      return uniform_dist(randEng);
    }

    KOD_API double generateRandomDoubleNumber(double min, double max)
    {
      static std::random_device randomDevice;
      static std::default_random_engine randEng(randomDevice());
      static std::uniform_real_distribution<double> uniform_dist(min, max);
      return uniform_dist(randEng);
    }
  */
  }
}