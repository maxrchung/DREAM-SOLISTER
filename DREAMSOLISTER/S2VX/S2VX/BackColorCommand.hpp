#pragma once
#include "BackCommand.hpp"
#include <glm/glm.hpp>
namespace S2VX {
	class BackColorCommand : public BackCommand {
	public:
		explicit BackColorCommand(Back& pBack, const int start, const int end, const EasingType easing, const float startR, const float startG, const float startB, const float endR, const float endG, const float endB);
		void update(const float easing);
		const glm::vec3& getEndColor() const { return endColor; }
		const glm::vec3& getStartColor() const { return startColor; }
	private:
		void validateBackColor(const glm::vec3& color) const;
		const glm::vec3 endColor;
		const glm::vec3 startColor;
	};
}