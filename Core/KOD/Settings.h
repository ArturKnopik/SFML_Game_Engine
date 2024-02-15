#pragma once
#include "KOD_export.h"

#include <iostream>
#include <string>

namespace KOD {
struct KOD_API Settings
{
	const char* name = "Unnamed app";
	unsigned int FPS = 60; // 0 - unlimited
	unsigned int windowsSizeX = 800;
	unsigned int windowsSizeY = 600;
	Settings() = default;
	Settings(unsigned int sizeX, unsigned int sizeY, const char* appName, unsigned int maxFPX) :
	    windowsSizeX(sizeX), windowsSizeY(sizeY), name(appName), FPS(maxFPX){};
	virtual ~Settings() = default;
};

extern const bool KOD_API debugMode;
} // namespace KOD

// some informations
// TODO: dt info: 1000000 = 1s (dt)