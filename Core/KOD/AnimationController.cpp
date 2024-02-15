#include "AnimationController.h"

KOD::AnimationController::AnimationController() : m_animationPtr(nullptr), m_currentFrame(0) {}

void KOD::AnimationController::update(const size_t dt)
{
	if (m_animationPtr) {
		if (!m_isPausedAnimation && m_animationPtr) {
			m_currentFrameTime += dt;
			if (m_customFixedFrameTime != 0) {
				if (m_currentFrameTime >= m_customFixedFrameTime) {
					m_currentFrameTime = 0;
					if (m_currentFrame + 1 < m_animationPtr->getSize()) {
						m_currentFrame++;
					} else {
						if (!m_isLoopedAnimation) {
							m_isPausedAnimation = true;
						} else {
							m_currentFrame = 0;
						}
					}
					setFrame(m_currentFrame, false);
				}
			} else if (m_currentFrameTime >= getAnimation()->getFrameTime(m_currentFrame)) {
				m_currentFrameTime = 0.0;
				if (m_currentFrame + 1 < m_animationPtr->getSize()) {
					m_currentFrame++;
				} else {
					if (!m_isLoopedAnimation) {
						m_isPausedAnimation = true;
					} else {
						m_currentFrame = 0;
					}
				}
				setFrame(m_currentFrame, false);
			}
		}
	}
}

void KOD::AnimationController::setAnimation(KOD::Animation& animation)
{
	m_animationPtr = &animation;
	m_texture = animation.getTexture();
	m_currentFrame = 0;
	setFrame(m_currentFrame);
}

void KOD::AnimationController::play() { m_isPausedAnimation = false; }

void KOD::AnimationController::pause() { m_isPausedAnimation = true; }

void KOD::AnimationController::stop()
{
	m_isPausedAnimation = true;
	m_currentFrame = 0;
	setFrame(m_currentFrame);
}

void KOD::AnimationController::setLooped(bool looped) { m_isLoopedAnimation = looped; }

const KOD::Animation* KOD::AnimationController::getAnimation() const { return m_animationPtr; }

bool KOD::AnimationController::isLooped() const { return m_isLoopedAnimation; }

bool KOD::AnimationController::isPlaying() const { return m_isPausedAnimation; }

double KOD::AnimationController::getFrameTime(std::size_t index) const
{
	if (m_customFixedFrameTime != 0) {
		return m_animationPtr->getFrameTime(index);
	}
	return m_customFixedFrameTime;
}

void KOD::AnimationController::setFrame(std::size_t newFrame, bool resetTime)
{
	if (m_animationPtr) {
		KOD::IntRect rect = m_animationPtr->getFrame(newFrame);
	}

	if (resetTime) {
		m_currentFrameTime = 0;
	}
}

const std::shared_ptr<sf::Texture> KOD::AnimationController::getTexture() const { return m_texture; }

const size_t KOD::AnimationController::getCurrentFrame() const { return m_currentFrame; }
