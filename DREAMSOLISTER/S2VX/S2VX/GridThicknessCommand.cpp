#include "GridThicknessCommand.hpp"
#include "Grid.hpp"
#include "ScriptError.hpp"
namespace S2VX {
	GridThicknessCommand::GridThicknessCommand(Grid& grid, const int start, const int end, const EasingType easing, const float pStartThickness, const float pEndThickness)
		: GridCommand{ grid, start, end, easing },
		startThickness{ pStartThickness },
		endThickness{ pEndThickness } {
		validateGridThickness(startThickness);
		validateGridThickness(endThickness);
	}
	void GridThicknessCommand::validateGridThickness(const float thickness) const {
		if (thickness < 0.0f) {
			throw ScriptError("Grid line thickness must be >= 0. Given: " + std::to_string(thickness));
		}
	}
	void GridThicknessCommand::update(const float easing) {
		const auto thickness = glm::mix(startThickness, endThickness, easing);
		grid.setThickness(thickness);
	}
}