#pragma
#include "KOD/Collider.h"
#include <memory>

namespace KOD
{
	class UIElement
	{
		std::vector<std::shared_ptr<UIElement>> m_uiElements;
	public:
		UIElement() = default;
		virtual void addUiElement(std::shared_ptr<UIElement> uiElement);
		virtual void removeUiElement(std::shared_ptr<UIElement> uiElement);
		virtual void isOverlaping(KOD::BoundingBox bb);

	};
}