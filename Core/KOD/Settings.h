#pragma once
#include "KOD_export.h"
#include <iostream>
#include <string>

namespace KOD {
  struct KOD_API Settings
  {
    std::string name = "Unnamed app";
    unsigned int FPS = 60; // 0 - unlimited
    unsigned int windowsSizeX = 800;
    unsigned int windowsSizeY = 600;
    Settings() = default;
    Settings(unsigned int sizeX, unsigned int sizeY, std::string appName, unsigned int maxFPX)
      :windowsSizeX(sizeX), windowsSizeY(sizeY), name(appName), FPS(maxFPX)
    {
    }
    virtual ~Settings() {};
  };

  extern  const bool KOD_API debugMode;
}

// some informations
//TODO: dt info: 1000000 = 1s (dt)