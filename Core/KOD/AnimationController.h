#pragma once
#include "Animation.h"
#include "KOD_export.h"
namespace KOD {
class KOD_API AnimationController
{
	const KOD::Animation* m_animationPtr;
	double m_customFixedFrameTime = 0; // change this value if want use fixed time frame time value
	double m_currentFrameTime = 0;
	std::size_t m_currentFrame = 0;
	bool m_isPausedAnimation = true;
	bool m_isLoopedAnimation = true;
	std::shared_ptr<sf::Texture> m_texture;

public:
	AnimationController();
	AnimationController(const AnimationController&) = default;
	void update(const size_t dt);
	void setAnimation(KOD::Animation& animation);
	void play();
	void pause();
	void stop();
	void setLooped(bool looped);
	const KOD::Animation* getAnimation() const;
	bool isLooped() const;
	bool isPlaying() const;
	double getFrameTime(std::size_t index = 0) const;
	void setFrame(std::size_t newFrame, bool resetTime = true);
	const std::shared_ptr<sf::Texture> getTexture() const;
	const size_t getCurrentFrame() const;
};
} // namespace KOD
