#include "CameraValues.hpp"
#include "CameraCommand.hpp"
#include "Display.hpp"
#include "Scripting.hpp"
#include "Sprite.hpp"
#include "SpriteColorCommand.hpp"
#include "SpriteFadeCommand.hpp"
#include "SpriteMoveCommand.hpp"
#include "SpriteRotateCommand.hpp"
#include "SpriteScaleCommand.hpp"
#include "Storyboard.hpp"

Vector3 convertglmvec3ToVector3(const glm::vec3& source) {
	return Vector3{ source.x, source.y, source.z };
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
	// TODO: Implement move constructor for Camera
	camera.update(time);

	auto cameraValues = CameraValues{ convertglmvec3ToVector3(camera.getPosition()), camera.getRoll(), camera.getScale() };
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

void convertS2VXToOsu(S2VX::Elements& elements) {
	auto& camera = elements.getCamera();
	for (const auto& S2VXsprite : elements.getSprites().getSprites()) {
		auto path = S2VXsprite->getTexture().getPath();
		auto sprite = new Sprite(path);
		for (const auto& command : S2VXsprite->getCommands()) {
			auto easing = convertS2VXEasingToOsuukiSBEasing(command->getEasing());
			auto startCamera = getCameraValuesAtMilliseconds(camera, command->getStart());
			auto endCamera = getCameraValuesAtMilliseconds(camera, command->getEnd());
			auto commandPointer = command.get();

			// yucklmao. I kind of regret using Command Pattern
			auto color = dynamic_cast<S2VX::SpriteColorCommand*>(commandPointer);
			if (color != nullptr) {
				auto startColor = convertS2VXColorToOsuukiSBColor(color->getStartColor());
				auto endColor = convertS2VXColorToOsuukiSBColor(color->getEndColor());
				sprite->Color(color->getStart(), color->getEnd(), startColor, endColor, easing);
			}

			auto fade = dynamic_cast<S2VX::SpriteFadeCommand*>(commandPointer);
			if (fade != nullptr) {
				sprite->Fade(fade->getStart(), fade->getEnd(), fade->getStartFade(), fade->getEndFade(), easing);
				continue;
			}

			auto move = dynamic_cast<S2VX::SpriteMoveCommand*>(commandPointer);
			if (move != nullptr) {
				auto startCoordinate = convertglmvec2ToVector2(move->getStartCoordinate());
				auto endCoordinate = convertglmvec2ToVector2(move->getEndCoordinate());
				sprite->Move(move->getStart(), move->getEnd(), startCoordinate, endCoordinate, easing);
				continue;
			}

			auto rotate = dynamic_cast<S2VX::SpriteRotateCommand*>(commandPointer);
			if (rotate != nullptr) {
				sprite->Rotate(move->getStart(), move->getEnd(), rotate->getStartRotation(), rotate->getEndRotation(), easing);
				continue;
			}

			auto scale = dynamic_cast<S2VX::SpriteScaleCommand*>(commandPointer);
			if (scale != nullptr) {
				sprite->Scale(scale->getStart(), scale->getEnd(), scale->getStart(), scale->getEnd(), easing);
				continue;
			}
		}
	}
}
int main() {
	S2VX::Display display;
	S2VX::Scripting scripting{ display };
	auto elements = scripting.evaluate("DREAMSOLISTER.chai");
	convertS2VXToOsu(elements);

	auto path = std::string(R"(X:\osu!\Songs\717639 TRUE - DREAM SOLISTER\TRUE - DREAM SOLISTER (Shiratoi).osb)");
	Storyboard::Instance()->Write(path);
	return 0;
}