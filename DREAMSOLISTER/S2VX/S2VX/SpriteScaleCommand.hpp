#pragma once
#include "SpriteCommand.hpp"
#include <glm/glm.hpp>
namespace S2VX {
	class SpriteScaleCommand : public SpriteCommand {
	public:
		explicit SpriteScaleCommand(Sprite* const sprite, const int start, const int end, const EasingType easing, const float pStartScaleX, const float pStartScaleY, const float pEndScaleX, const float pEndScaleY);
		void update(const float easing);
		const glm::vec2& getEndScale() const { return endScale; }
		const glm::vec2& getStartScale() const { return startScale; }
	private:
		void validateSpriteScale(const glm::vec2& scale) const;
		const glm::vec2 endScale;
		const glm::vec2 startScale;
	};
}