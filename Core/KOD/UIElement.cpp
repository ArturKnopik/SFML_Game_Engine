#include "UiElement.h"

KOD::UiElement::UiElement(BoundingBox psoition) : m_uiPosition(m_uiPosition) {}

void KOD::UiElement::addUiElement(std::shared_ptr<KOD::UiElement> uiElement)
{
	if (!uiElement) {
		return;
	}

	auto element = std::find(m_uiElements.begin(), m_uiElements.end(), uiElement);
	if (element != m_uiElements.end()) {
		return;
	}

	m_uiElements.push_back(element);
}

void KOD::UiElement::removeUiElement(std::shared_ptr<UiElement> uiElement)
{
	auto element = std::find(m_uiElements.begin(), m_uiElements.end(), uiElement);
	if (element != m_uiElements.end()) {
		return;
	}
	m_uiElements.erase(element);
}

void KOD::UiElement::isOverlaping(KOD::BoundingBox bb) {

}

std::vector<std::shared_ptr<KOD::UiElement>>& KOD::UiElement::getUiElements() { return m_uiElements; }

void KOD::UiElement::draw(sf::RenderWindow& window)
{
	for (auto& uiElement : m_uiElements) {
		uiElement->draw(window);
	}
}
