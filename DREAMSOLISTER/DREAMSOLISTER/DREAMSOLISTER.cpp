#include "Display.hpp"
#include "Scripting.hpp"
#include "Sprite.hpp"
#include "SpriteFadeCommand.hpp"
#include "SpriteMoveCommand.hpp"
#include "SpriteRotateCommand.hpp"
#include "SpriteScaleCommand.hpp"


void convertToOsu(S2VX::Elements& elements) {
	for (const auto& S2VXsprite : elements.getSprites().getSprites()) {
		auto path = S2VXsprite->getTexture().getPath();
		auto sprite = new Sprite(path);
		for (const auto& command : S2VXsprite->getCommands()) {
			// yucklmao. I kind of regret using Command Pattern
			auto fade = dynamic_cast<S2VX::SpriteFadeCommand*>(command.get());
			if (fade != nullptr) {
				continue;
			}
			auto move = dynamic_cast<S2VX::SpriteMoveCommand*>(command.get());
			if (move != nullptr) {
				// Cast failed
				continue;
			}
			auto rotate = dynamic_cast<S2VX::SpriteRotateCommand*>(command.get());
			if (rotate != nullptr) {

				continue;
			}
			auto scale = dynamic_cast<S2VX::SpriteScaleCommand*>(command.get());
			if (scale != nullptr) {
				continue;
			}
		}
	}
}

int main() {
	S2VX::Display display;
	S2VX::Scripting scripting{ display };
	auto elements = scripting.evaluate("DREAMSOLISTER.chai");
	convertToOsu(elements);
	auto path = std::string(R"(X:\osu!\Songs\717639 TRUE - DREAM SOLISTER\TRUE - DREAM SOLISTER(Shiratoi).osb)");
	return 0;
}