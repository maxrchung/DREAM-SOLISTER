#pragma once
#include "GridCommand.hpp"
namespace S2VX {
	class GridFadeCommand : public GridCommand {
	public:
		explicit GridFadeCommand(Grid& grid, const int start, const int end, const EasingType easing, const float pStartFade, const float pEndFade);
		void update(const float easing);
	private:
		void validateGridFade(const float) const;
		const float endFade;
		const float startFade;
	};
}