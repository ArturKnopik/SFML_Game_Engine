#pragma
#include "UiElement.h"

#include <SFML/Window/Event.hpp>
#include <cstdint>

namespace KOD {
enum UiState;

class UiHandler : public KOD::UiElement
{
public:
	UiHandler() = default;
	void update(size_t dt, float mouseX, float mouseY);

private:
};
} // namespace KOD