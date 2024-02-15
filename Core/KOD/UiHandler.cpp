#include "UiHandler.h"

void KOD::UiHandler::update(size_t dt, float mouseX, float mouseY)
{
	for (auto& it : getUiElements()) {
		it->onStateChanged(KOD::UiState::DEFAULT);
		it->onMouseEnter();
		it->onMouseLeave();
		it->onMouseMoved(mouseX, mouseY);
		it->onMousePressed(mouseX, mouseY);
		it->onMouseReleased(mouseX, mouseY);
		it->onMouseWheelMoved(dt);
	}
}