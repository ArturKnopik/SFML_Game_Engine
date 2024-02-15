#pragma once
#include "Frame.h"
#include "KOD_export.h"
#include "SFML/Graphics/Sprite.hpp"

#include <memory>
#include <vector>

namespace KOD {

class KOD_API Animation
{
	std::shared_ptr<sf::Texture> m_texture;
	std::vector<KOD::Frame> m_frameList;

public:
	Animation();
	~Animation();
	void addFrame(KOD::Frame frame);
	void setTexture(std::shared_ptr<sf::Texture> texture);
	const std::shared_ptr<sf::Texture> getTexture() const;
	const IntRect getFrame(std::size_t index) const;
	const double getFrameTime(std::size_t index) const;
	std::size_t getSize() const;
};
} // namespace KOD
