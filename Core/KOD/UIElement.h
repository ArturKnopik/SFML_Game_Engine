#pragma

#include "DefinesUtil.h"
#include "ICollider.h"
#include "KOD_export.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

namespace KOD {
enum KOD_API UiState
{
	DEFAULT,
	HOVER,
	PRESSED,
	FOCUS
};

class KOD_API UiElement
{
	std::vector<std::shared_ptr<UiElement>> m_uiElements;
	KOD::BoundingBox m_uiPosition;

public:
	UiElement() = default;
	UiElement(BoundingBox psoition);
	virtual ~UiElement() = default;
	void addUiElement(std::shared_ptr<UiElement> uiElement);
	void removeUiElement(std::shared_ptr<UiElement> uiElement);
	void isOverlaping(KOD::BoundingBox bb);
	std::vector<std::shared_ptr<UiElement>> &getUiElements();

	void draw(sf::RenderWindow &window);

	virtual void onStateChanged(UiState state) { UNUSED(state); };
	virtual void onMouseEnter(){};
	virtual void onMouseLeave(){};
	virtual void onMouseMoved(float x, float y)
	{
		UNUSED(x);
		UNUSED(y);
	};
	virtual void onMousePressed(float x, float y)
	{
		UNUSED(x);
		UNUSED(y);
	};
	virtual void onMouseReleased(float x, float y)
	{
		UNUSED(x);
		UNUSED(y);
	};
	virtual void onMouseWheelMoved(const size_t dt) { UNUSED(dt); };
};
} // namespace KOD