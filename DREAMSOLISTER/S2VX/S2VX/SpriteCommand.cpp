#include "SpriteCommand.hpp"
namespace S2VX {
	SpriteCommand::SpriteCommand(Sprite* const pSprite, const int start, const int end, const EasingType easing)
		: Command{ start, end, easing },
		sprite{ pSprite } {}
}