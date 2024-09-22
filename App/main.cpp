#include "FarmGameState.h"
#include "game.h"

#include <Json.h>

int main()
{
#ifdef _DEBUG
	g_logger.setLogLevel(kod::Logger::LogSeverity::DEBUG);
#else
	g_logger.setLogLevel(kod::Logger::LogSeverity::ERROR);
#endif
	g_logger.clearLogFile();

	kod::Game game = kod::Game("Test Game");
	game.pushState(std::make_shared<FarmGameState>(game));

	game.run();
}