#include "CameraValues.hpp"
#include "SpriteBinding.hpp"
#include "S2VX/CameraCommand.hpp"
#include "S2VX/Display.hpp"
#include "S2VX/Scripting.hpp"
#include "S2VX/Sprite.hpp"
#include "S2VX/SpriteColorCommand.hpp"
#include "S2VX/SpriteFadeCommand.hpp"
#include "S2VX/SpriteMoveCommand.hpp"
#include "S2VX/SpriteRotateCommand.hpp"
#include "S2VX/SpriteScaleCommand.hpp"
#include "OsuukiSB/Storyboard.hpp"
#include <iostream>

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

	auto cameraValues = CameraValues{ Vector2{ camera.getPosition().x, camera.getPosition().y}, camera.getRoll(), camera.getScale() };
	return cameraValues;
}

Easing convertS2VXEasingToOsuukiSBEasing(S2VX::EasingType source) {
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


Vector2 convertglmvec2ToVector2(const glm::vec2& source) {
	return Vector2{ source.x, source.y };
}

Vector2 convertCoordinatesToPosition(glm::vec2 coordinates, const CameraValues& cameraValues) {
	auto position = convertglmvec2ToVector2(coordinates) * cameraValues.scale;
	auto translatePosition = position - cameraValues.position;
	auto rotatePosition = translatePosition.Rotate(cameraValues.roll);
	return rotatePosition;
}

float convertDegreesToRadians(float radians) {
	return radians * 3.14159f / 180.0f;
}

void convertS2VXSpritesToOsu(S2VX::Camera& camera, std::vector<SpriteBinding> spriteBindings) {
	for (auto binding: spriteBindings) {
		auto S2VXSprite = binding.S2VXSprite;
		auto sprite = binding.sprite;
		for (const auto& command : S2VXSprite->getCommands()) {
			auto easing = convertS2VXEasingToOsuukiSBEasing(command->getEasing());
			auto start = command->getStart();
			auto end = command->getEnd();
			auto startCameraValues = getCameraValuesAtMilliseconds(camera, start);
			auto endCameraValues = getCameraValuesAtMilliseconds(camera, end);

			// yucklmao. I kind of regret using Command Pattern
			auto commandPointer = command.get();
			auto color = dynamic_cast<S2VX::SpriteColorCommand*>(commandPointer);
			if (color != nullptr) {
				auto startColor = convertS2VXColorToOsuukiSBColor(color->getStartColor());
				auto endColor = convertS2VXColorToOsuukiSBColor(color->getEndColor());
				sprite->Color(start, end, startColor, endColor, easing);
			}

			auto fade = dynamic_cast<S2VX::SpriteFadeCommand*>(commandPointer);
			if (fade != nullptr) {
				sprite->Fade(start, end, fade->getStartFade(), fade->getEndFade(), easing);
				continue;
			}

			auto move = dynamic_cast<S2VX::SpriteMoveCommand*>(commandPointer);
			if (move != nullptr) {
				auto startPosition = convertCoordinatesToPosition(move->getStartCoordinate(), startCameraValues);
				auto endPosition = convertCoordinatesToPosition(move->getEndCoordinate(), endCameraValues);

				sprite->Move(start, end, startPosition, endPosition, easing);
				continue;
			}

			auto rotate = dynamic_cast<S2VX::SpriteRotateCommand*>(commandPointer);
			if (rotate != nullptr) {
				auto startRotation = convertDegreesToRadians(rotate->getStartRotation());
				auto endRotation = convertDegreesToRadians(rotate->getEndRotation());
				sprite->Rotate(start, end, startRotation, endRotation, easing);
				continue;
			}

			auto scale = dynamic_cast<S2VX::SpriteScaleCommand*>(commandPointer);
			if (scale != nullptr) {
				sprite->Scale(start, end, scale->getStart(), scale->getEnd(), easing);
				continue;
			}
		}
	}
}

std::vector<SpriteBinding> createSpriteBindings(const std::vector<std::unique_ptr<S2VX::Sprite>>& S2VXSprites) {
	auto spriteBindings = std::vector<SpriteBinding>(S2VXSprites.size());
	for (auto i = 0; i < spriteBindings.size(); ++i) {
		spriteBindings[i] = SpriteBinding{ S2VXSprites[i].get() };
	}
	return spriteBindings;
}

int main() {
	S2VX::Display display;
	S2VX::Scripting scripting{ display };
	auto& elements = scripting.evaluate("DREAMSOLISTER.chai");
	auto spriteBindings = createSpriteBindings(elements.getSprites().getSprites());
	convertS2VXSpritesToOsu(elements.getCamera(), spriteBindings);

	auto path = std::string(R"(X:\osu!\Songs\717639 TRUE - DREAM SOLISTER\TRUE - DREAM SOLISTER (Shiratoi).osb)");
	Storyboard::Instance()->Write(path);
	return 0;
}