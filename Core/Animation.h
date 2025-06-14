#pragma once

#include "export.h"

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <unordered_map>

namespace kod {

class Frame
{
public:
	KOD_API Frame() = delete;
	KOD_API ~Frame() = default;
	KOD_API Frame(sf::IntRect imagePosition, size_t time = 10000000);
	KOD_API const size_t getDuration() const;
	KOD_API const sf::IntRect getFrameRect() const;
	KOD_API void setTexture(std::shared_ptr<sf::Texture> texture);
	KOD_API const std::shared_ptr<sf::Texture> getTexture() const;

private:
	size_t m_timeToNextFrame = 10000;
	sf::IntRect m_imagePosition = {{0, 0}, {0, 0}};
	std::shared_ptr<sf::Texture> m_texture = nullptr;
};

class Animation
{
public:
	KOD_API Animation() = default;
	KOD_API ~Animation() = default;
	KOD_API void addFrame(Frame frame);
	KOD_API const Frame& getCurrentFrame() const;
	KOD_API void update(const size_t dt);
	KOD_API void reset();
	KOD_API void isSynchronized(bool synchronized);
	KOD_API bool isSynchronized();
	KOD_API bool hasFrame();

private:
	std::vector<Frame> m_frameList;
	size_t m_currentFrameIndex = 0;
	size_t m_frameTime = 0;
	size_t m_isSynchronized = false;
};

} // namespace kod
