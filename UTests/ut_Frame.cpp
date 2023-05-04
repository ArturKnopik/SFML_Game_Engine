#include "pch.h"
#include "../Core/KOD/Frame.h"

TEST(UT_FRAME, ut_Frame_sanity) {

	sf::IntRect imagePosition(100, 100, 100, 100);
	int timeToNextFrame = 10000;
	KOD::Frame frame(imagePosition, timeToNextFrame);
	EXPECT_EQ(frame.getFrameRect(), imagePosition);
	EXPECT_EQ(frame.getMaxFrameTime(), timeToNextFrame * 1000);
}