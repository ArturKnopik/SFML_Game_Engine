#include "pch.h" // must be first

#include "../Core/Animation.h"

//namespace Particle {


TEST(Animation_Frame, UT_Frame)
{
	kod::Frame frame({ { 0,0},{100,100} }, 12345);

	EXPECT_EQ(frame.getDuration(), 12345);
}

//}