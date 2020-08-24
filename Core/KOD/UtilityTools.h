#pragma once
#include "KOD_export.h"
#include "Settings.h"
#include <random>

namespace KOD {
  void KOD_API sendDebugInformation(std::string message);

  int KOD_API generateRandomIntNumber(int min, int max);
 
  double KOD_API generateRandomDoubleNumber(double min, double max);
}