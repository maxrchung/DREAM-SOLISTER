#include "CameraValues.hpp"
#include "SpriteBinding.hpp"
#include "S2VX/BackColorCommand.hpp"
#include "S2VX/CameraCommand.hpp"
#include "S2VX/CameraMoveCommand.hpp"
#include "S2VX/CameraRotateCommand.hpp"
#include "S2VX/CameraZoomCommand.hpp"
#include "S2VX/Display.hpp"
#include "S2VX/Scripting.hpp"
#include "S2VX/ScriptError.hpp"
#include "S2VX/Sprite.hpp"
#include "S2VX/SpriteColorCommand.hpp"
#include "S2VX/SpriteFadeCommand.hpp"
#include "S2VX/SpriteMoveCommand.hpp"
#include "S2VX/SpriteRotateCommand.hpp"
#include "S2VX/SpriteScaleCommand.hpp"
#include "OsuukiSB/Storyboard.hpp"
#include <iostream>

// All images have the same fixed width
int imageWidth = 100;
// Quarter beat
int quarter = 360;

std::string addWithNewLine(const char* what) {
	std::string message(what);
	if (message.size() > 0 && message[message.size() - 1] == '\n') {
		return message;
	}
	else {
		return message + "\n";
	}
}

Vector2 convertglmvec2ToVector2(const glm::vec2& source) {
	return Vector2{ source.x, source.y };
}

Vector2 convertCoordinatesToPosition(const glm::vec2& coordinates, const CameraValues& cameraValues) {
	const auto position = convertglmvec2ToVector2(coordinates) * cameraValues.scale;
	const auto translatePosition = position - cameraValues.position;
	const auto rotatePosition = translatePosition.Rotate(cameraValues.roll);
	return rotatePosition;
}

float convertDegreesToRadians(const float radians) {
	return radians * 3.14159f / 180.0f;
}

Easing convertS2VXEasingToOsuukiSBEasing(const S2VX::EasingType source) {
	switch (source) {
		case S2VX::EasingType::LinearInterpolation:
			return Easing::Linear;
		case S2VX::EasingType::QuadraticEaseIn:
			return Easing::QuadIn;
		case S2VX::EasingType::QuadraticEaseOut:
			return Easing::QuadOut;
		case S2VX::EasingType::QuadraticEaseInOut:
			return Easing::QuadInOut;
		case S2VX::EasingType::CubicEaseIn:
			return Easing::CubicIn;
		case S2VX::EasingType::CubicEaseOut:
			return Easing::CubicOut;
		case S2VX::EasingType::CubicEaseInOut:
			return Easing::CubicInOut;
		case S2VX::EasingType::QuarticEaseIn:
			return Easing::QuartIn;
		case S2VX::EasingType::QuarticEaseOut:
			return Easing::QuartOut;
		case S2VX::EasingType::QuarticEaseInOut:
			return Easing::QuartInOut;
		case S2VX::EasingType::QuinticEaseIn:
			return Easing::QuintIn;
		case S2VX::EasingType::QuinticEaseOut:
			return Easing::QuintOut;
		case S2VX::EasingType::QuinticEaseInOut:
			return Easing::QuintInOut;
		case S2VX::EasingType::SineEaseIn:
			return Easing::SineIn;
		case S2VX::EasingType::SineEaseOut:
			return Easing::SineOut;
		case S2VX::EasingType::SineEaseInOut:
			return Easing::SineInOut;
		case S2VX::EasingType::CircularEaseIn:
			return Easing::CircIn;
		case S2VX::EasingType::CircularEaseOut:
			return Easing::CircOut;
		case S2VX::EasingType::CircularEaseInOut:
			return Easing::CircInOut;
		case S2VX::EasingType::ExponentialEaseIn:
			return Easing::ExpoIn;
		case S2VX::EasingType::ExponentialEaseOut:
			return Easing::ExpoOut;
		case S2VX::EasingType::ExponentialEaseInOut:
			return Easing::ExpoInOut;
		case S2VX::EasingType::ElasticEaseIn:
			return Easing::ElasticIn;
		case S2VX::EasingType::ElasticEaseOut:
			return Easing::ElasticOut;
		case S2VX::EasingType::ElasticEaseInOut:
			return Easing::ElasticInOut;
		case S2VX::EasingType::BackEaseIn:
			return Easing::BackIn;
		case S2VX::EasingType::BackEaseOut:
			return Easing::BackOut;
		case S2VX::EasingType::BackEaseInOut:
			return Easing::BackInOut;
		case S2VX::EasingType::BounceEaseIn:
			return Easing::BounceIn;
		case S2VX::EasingType::BounceEaseOut:
			return Easing::BounceOut;
		case S2VX::EasingType::BounceEaseInOut:
			return Easing::BounceInOut;
		default:
			return Easing::Linear;
	}
}

Color convertS2VXColorToOsuukiSBColor(const glm::vec3& source) {
	return Color{ 255.0f * source.x, 255.0f * source.y, 255.0f * source.z };
}

void processBackground(const S2VX::Back& back) {
	auto bg = new Sprite("pixel.png", Vector2::Zero, Layer::Background);

	bg->ScaleVector(29187, 30624, Vector2(0,0), Vector2::ScreenSize, Easing::EasingIn);
	bg->Fade(29187, 30624, 0, 1, Easing::EasingIn);
	bg->ScaleVector(67989, 70863, Vector2::ScreenSize, Vector2(0, 0), Easing::EasingOut);
	bg->Fade(67989, 70863, 1, 0, Easing::EasingOut);

	for (const auto& command : back.getCommands()) {
		const auto start = command->getStart();
		const auto end = command->getEnd();
		const auto easing = convertS2VXEasingToOsuukiSBEasing(command->getEasing());

		const auto commandPointer = command.get();
		const auto color = dynamic_cast<S2VX::BackColorCommand*>(commandPointer);
		if (color != nullptr) {
			const auto startColor = convertS2VXColorToOsuukiSBColor(color->getStartColor());
			const auto endColor = convertS2VXColorToOsuukiSBColor(color->getEndColor());
			bg->Color(start, end, startColor, endColor, easing);
			continue;
		}
	}
}

void setBorder() {
	const auto borderOffset = 25.0f;
	const auto halfSize = Vector2::ScreenSize / 2;
	const auto color = Color(0.0f, 169.0f, 195.0f);
	const auto width = 10.0f;
	const auto horizontal = Vector2(Vector2::ScreenSize.x - 2 * borderOffset + width, width);
	const auto vertical = Vector2(width, Vector2::ScreenSize.y - 2 * borderOffset + width);

	auto top = new Sprite("pixel.png", Vector2(0.0f, halfSize.y - borderOffset));
	top->Color(29187, 29187, color, color);
	top->ScaleVector(29187, 30624, Vector2(width, width), horizontal, Easing::EasingIn);
	top->Fade(29187, 30624, 0, 1, Easing::EasingIn);
	top->ScaleVector(67989, 70863, horizontal, Vector2(width, width), Easing::EasingOut);
	top->Fade(67989, 70863, 1, 0, Easing::EasingOut);

	auto bottom = new Sprite("pixel.png", Vector2(0.0f, -(halfSize.y - borderOffset)));
	bottom->Color(29187, 29187, color, color);
	bottom->ScaleVector(29187, 30624, Vector2(width, width), horizontal, Easing::EasingIn);
	bottom->ScaleVector(67989, 70863, horizontal, Vector2(width, width), Easing::EasingOut);
	bottom->Fade(67989, 70863, 1, 0, Easing::EasingOut);

	auto right = new Sprite("pixel.png", Vector2(-(halfSize.x - borderOffset), 0.0f));
	right->Color(29187, 29187, color, color);
	right->ScaleVector(29187, 30624, Vector2(width, width), vertical, Easing::EasingIn);
	right->ScaleVector(67989, 70863, vertical, Vector2(width, width), Easing::EasingOut);
	right->Fade(67989, 70863, 1, 0, Easing::EasingOut);

	auto left = new Sprite("pixel.png", Vector2(halfSize.x - borderOffset, 0.0f));
	left->Color(29187, 29187, color, color);
	left->ScaleVector(29187, 30624, Vector2(width, width), vertical, Easing::EasingIn);
	left->ScaleVector(67989, 70863, vertical, Vector2(width, width), Easing::EasingOut);
	left->Fade(67989, 70863, 1, 0, Easing::EasingOut);
}

void setS2VXBorder() {
	const auto borderOffset = 120.0f;
	const auto halfSize = Vector2(Vector2::ScreenSize.y / 2, Vector2::ScreenSize.y / 2);
	const auto color = Color(0.0f, 169.0f, 195.0f);
	const auto width = 10.0f;
	const auto horizontal = Vector2(Vector2::ScreenSize.y - 2 * borderOffset + width, width);
	const auto vertical = Vector2(width, Vector2::ScreenSize.y - 2 * borderOffset + width);

	const auto start = 804;
	const auto fadeStart = start - quarter * 2;
	const auto end = 1882;
	const auto fadeEnd = end + quarter * 2;

	auto bg = new Sprite("pixel.png", Vector2::Zero, Layer::Background);
	bg->Scale(fadeStart, start, 0, horizontal.x, Easing::EasingIn);
	bg->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	bg->Scale(end, fadeEnd, horizontal.x, 0, Easing::EasingOut);
	bg->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);

	auto top = new Sprite("pixel.png", Vector2(0.0f, halfSize.y - borderOffset));
	top->Color(0, 0, color, color);
	top->ScaleVector(fadeStart, start, Vector2(width, width), horizontal, Easing::EasingIn);
	top->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	top->ScaleVector(end, fadeEnd, horizontal, Vector2(width, width), Easing::EasingOut);
	top->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);

	auto bottom = new Sprite("pixel.png", Vector2(0.0f, -(halfSize.y - borderOffset)));
	bottom->Color(0, 0, color, color);
	bottom->ScaleVector(fadeStart, start, Vector2(width, width), horizontal, Easing::EasingIn);
	bottom->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	bottom->ScaleVector(end, fadeEnd, horizontal, Vector2(width, width), Easing::EasingOut);
	bottom->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);

	auto right = new Sprite("pixel.png", Vector2(-(halfSize.x - borderOffset), 0.0f));
	right->Color(0, 0, color, color);
	right->ScaleVector(fadeStart, start, Vector2(width, width), vertical, Easing::EasingIn);
	right->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	right->ScaleVector(end, fadeEnd, vertical, Vector2(width, width), Easing::EasingOut);
	right->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);

	auto left = new Sprite("pixel.png", Vector2(halfSize.x - borderOffset, 0.0f));
	left->Color(0, 0, color, color);
	left->ScaleVector(fadeStart, start, Vector2(width, width), vertical, Easing::EasingIn);
	left->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	left->ScaleVector(end, fadeEnd, vertical, Vector2(width, width), Easing::EasingOut);
	left->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);
}

S2VX::SpriteMoveCommand* getS2VXMoveCommand(const std::vector<std::unique_ptr<S2VX::Command>>& commands) {
	for (const auto& command : commands) {
		const auto move = dynamic_cast<S2VX::SpriteMoveCommand*>(command.get());
		if (move != nullptr) {
			return move;
		}
	}
	return nullptr;
}

CameraValues getCameraValuesAtMilliseconds(S2VX::Camera& camera, const int time) {
	for (const auto& command : camera.getCommands()) {
		if (command->getStart() <= time) {
			camera.update(command->getStart());
		}
		else {
			break;
		}
	}
	camera.update(time);

	const auto cameraValues = CameraValues{ Vector2{ camera.getPosition().x, camera.getPosition().y }, camera.getRoll(), camera.getScale() };
	return cameraValues;
}

std::vector<SpriteBinding> createSpriteBindings(const std::vector<std::unique_ptr<S2VX::Sprite>>& S2VXSprites, S2VX::Camera& camera) {
	auto spriteBindings = std::vector<SpriteBinding>(S2VXSprites.size());
	for (auto i = 0; i < spriteBindings.size(); ++i) {
		const auto sprite = S2VXSprites[i].get();
		const auto move = getS2VXMoveCommand(sprite->getCommands());
		const auto path = sprite->getTexture().getPath();
		const auto cameraValues = getCameraValuesAtMilliseconds(camera, sprite->getStart());
		const auto center = convertCoordinatesToPosition(move->getStartCoordinate(), cameraValues);
		const auto scale = cameraValues.scale / imageWidth;
		const auto spriteGroup = SpriteGroup(path, imageWidth, move->getStart(), move->getEnd(), center, cameraValues.roll, scale, quarter * 2);
		spriteBindings[i] = SpriteBinding{ S2VXSprites[i].get(), spriteGroup };
	}
	return spriteBindings;
}

void processS2VXSprites(S2VX::Camera& camera, const std::vector<SpriteBinding>& spriteBindings) {
	for (auto binding: spriteBindings) {
		const auto S2VXSprite = binding.S2VXSprite;
		auto spriteGroup = binding.spriteGroup;
		for (const auto& command : S2VXSprite->getCommands()) {
			const auto easing = convertS2VXEasingToOsuukiSBEasing(command->getEasing());
			const auto start = command->getStart();
			const auto end = command->getEnd();

			// yucklmao. I kind of regret using Command Pattern
			const auto commandPointer = command.get();
			const auto color = dynamic_cast<S2VX::SpriteColorCommand*>(commandPointer);
			if (color != nullptr) {
				const auto startColor = convertS2VXColorToOsuukiSBColor(color->getStartColor());
				const auto endColor = convertS2VXColorToOsuukiSBColor(color->getEndColor());
				for (auto sprite : spriteGroup.sprites) {
					sprite->Color(start, end, startColor, endColor, easing);
				}
				continue;
			}

			const auto fade = dynamic_cast<S2VX::SpriteFadeCommand*>(commandPointer);
			if (fade != nullptr) {
				for (auto sprite : spriteGroup.sprites) {
					sprite->Fade(start, end, fade->getStartFade(), fade->getEndFade(), easing);
				}
				continue;
			}
		}
	}
}

void processCamera(S2VX::Camera& camera, const std::vector<SpriteBinding>& spriteBindings) {
	// Use ints so in order
	std::set<int> actives;
	int nextActive = 0;
	for (const auto& command : camera.getCommands()) {
		const auto start = command->getStart();
		const auto end = command->getEnd();

		// Remove active binding if end < start
		for (auto active = actives.begin(); active != actives.end(); ) {
			const auto S2VXSprite = spriteBindings[(*active)].S2VXSprite;
			if (S2VXSprite->getEnd() < start) {
				active = actives.erase(active);
			}
			else {
				++active;
			}
		}

		while (nextActive != spriteBindings.size() && spriteBindings[nextActive].S2VXSprite->getStart() <= start) {
			actives.insert(nextActive++);
		}

		// Update sprites
		const auto commandPointer = command.get();
		const auto easing = convertS2VXEasingToOsuukiSBEasing(command->getEasing());
		camera.update(command->getEnd());
		for (auto active : actives) {
			auto spriteGroup = spriteBindings[active].spriteGroup;
			const auto center = spriteGroup.center;

			const auto move = dynamic_cast<S2VX::CameraMoveCommand*>(commandPointer);
			if (move != nullptr) {
				const auto distance = move->getEndCoordinate() - move->getStartCoordinate();
				const auto convertDistance = convertglmvec2ToVector2(distance);
				const auto cameraValues = CameraValues(Vector2{ camera.getPosition().x, camera.getPosition().y }, camera.getRoll(), camera.getScale());
				const auto scaleDistance = convertDistance * cameraValues.scale;
				for (auto sprite : spriteGroup.sprites) {
					// Minus to account for reverse
					const auto movePosition = sprite->position - scaleDistance;
					sprite->Move(start, end, sprite->position, movePosition, easing);
				}
				const auto centerPosition = center + scaleDistance;
				spriteGroup.center = centerPosition;
				continue;
			}

			auto rotate = dynamic_cast<S2VX::CameraRotateCommand*>(commandPointer);
			if (rotate != nullptr) {
				// Local rotation
				const auto startRotation = convertDegreesToRadians(rotate->getStartRotation());
				const auto endRotation = convertDegreesToRadians(rotate->getEndRotation());
				const auto rotation = endRotation - startRotation;
				
				// Movement adjustment
				const auto rotatePosition = center.Rotate(rotation);
				const auto rotateDistance = rotatePosition - center;

				// Apply together
				for (auto sprite : spriteGroup.sprites) {
					const auto localRotatePosition = sprite->position.Rotate(rotation);
					sprite->Move(start, end, sprite->position, localRotatePosition, easing);

					sprite->Rotate(start, end, sprite->rotation, sprite->rotation + rotation, easing);
				}
				const auto centerPosition = center + rotateDistance;
				spriteGroup.center = centerPosition;
				continue;
			}

			const auto zoom = dynamic_cast<S2VX::CameraZoomCommand*>(commandPointer);
			if (zoom != nullptr) {
				const auto startScale = zoom->getStartScale() / imageWidth;
				const auto endScale = zoom->getEndScale() / imageWidth;
				const auto scale = endScale / startScale;
				const auto normalizePosition = center.Normalize();
				const auto magnitude = center.Magnitude();
				const auto scalePosition = normalizePosition * (scale * magnitude);

				for (auto sprite : spriteGroup.sprites) {
					sprite->Scale(start, end, sprite->scale, endScale, easing);
					const auto localDifference = sprite->position - center;
					const auto localMagnitude = localDifference.Magnitude();
					const auto localNormalize = localDifference.Normalize();
					const auto spritePosition = scalePosition + localNormalize * (scale * localMagnitude);
					sprite->Move(start, end, sprite->position, spritePosition, easing);
				}
				spriteGroup.center = scalePosition;
				continue;
			}
		}
	}
}

void main() {
	try {
		srand(time(NULL));

		S2VX::Display display;
		S2VX::Scripting scripting{ display };
		auto& elements = scripting.evaluate("DREAMSOLISTER.chai");

		processBackground(elements.getBack());

		// Blue line rectangle border
		setBorder();
		//setS2VXBorder();

		auto spriteBindings = createSpriteBindings(elements.getSprites().getSprites(), elements.getCamera());
		processS2VXSprites(elements.getCamera(), spriteBindings);
		processCamera(elements.getCamera(), spriteBindings);
		// Destroy sprite bindings
		std::for_each(spriteBindings.begin(), spriteBindings.end(), [](SpriteBinding& binding) { binding.spriteGroup.destroy(); });

		auto path = std::string(R"(X:\osu!\Songs\717639 TRUE - DREAM SOLISTER\TRUE - DREAM SOLISTER (Shiratoi).osb)");
		Storyboard::Instance()->Write(path);
	}
	catch (const chaiscript::exception::eval_error &e) {
		std::cout << "ChaiScript Exception" << std::endl << addWithNewLine(e.pretty_print().c_str());
		std::cin.get();
	}
	catch (const S2VX::ScriptError &e) {
		std::cout << "Script Error" << std::endl << addWithNewLine(e.what());
		std::cin.get();
	}
	catch (const std::exception &e) {
		std::cout << "General Exception" << std::endl << addWithNewLine(e.what());
		std::cin.get();
	}
}