#include "CameraValues.hpp"
#include "MusicSheet.hpp"
#include "SpriteBinding.hpp"
#include "ShapeAnimation.hpp"
#include "S2RYBRUH/Storyboard.hpp"
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
#include <iostream>

// All images have the same fixed width
int imageWidth = 100;
// Quarter beat
int quarter = 360; // 359.28144f
int moveParallax = quarter / 4;

Vector2 convertglmvec2ToVector2(const glm::vec2& source) {
	return Vector2{ source.x, source.y };
}

Vector2 convertCoordinatesToPosition(const glm::vec2& coordinates, const CameraValues& cameraValues) {
	const auto position = convertglmvec2ToVector2(coordinates) * cameraValues.scale;
	const auto translatePosition = position - cameraValues.position;
	const auto rotatePosition = translatePosition.Rotate(cameraValues.roll);
	return rotatePosition;
}

float convertDegreesToRadians(const float degrees) {
	return degrees * 3.14159f / 180.0f;
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

void processBackground(Sprite* const bg) {
	const auto screenSquare = Vector2(Vector2::ScreenSize.x, Vector2::ScreenSize.x);
	bg->ScaleVector(29187, 30624, Vector2(0, 0), screenSquare, Easing::EasingIn);
	bg->Fade(29187, 30624, 0, 1, Easing::EasingIn);
	bg->ScaleVector(67989, 70145, screenSquare, Vector2(0, 0), Easing::EasingOut);
	bg->Fade(67989, 70145, 1, 0, Easing::EasingOut);

	bg->ScaleVector(103738, 105354, Vector2(0, 0), screenSquare, Easing::EasingIn);
	bg->Fade(103738, 105354, 0, 1, Easing::EasingIn);
	bg->ScaleVector(147929, 150265, screenSquare, Vector2(0, 0), Easing::EasingOut);
	bg->Fade(147929, 150265, 1, 0, Easing::EasingOut);

	bg->ScaleVector(179187, 180444, Vector2(0, 0), screenSquare, Easing::EasingIn);
	bg->Fade(179187, 180444, 0, 1, Easing::EasingIn);
	bg->ScaleVector(201642, 203079, screenSquare, Vector2(0, 0), Easing::EasingOut);
	bg->Fade(201642, 203079, 1, 0, Easing::EasingOut);

	bg->ScaleVector(228947, 231103, Vector2(0, 0), screenSquare, Easing::EasingIn);
	bg->Fade(228947, 231103, 0, 1, Easing::EasingIn);
	bg->ScaleVector(279247, 280684, screenSquare, Vector2(0, 0), Easing::EasingOut);
	bg->Fade(279247, 280684, 1, 0, Easing::EasingOut);
}

void processScriptBackground(const S2VX::Back& back, Sprite* const bg) {
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

void setDotBackground(const int startFadeIn, const int endFadeIn, const int startFadeOut, const int endFadeOut) {
	const auto numDots = 50;
	const auto dotDistance = 200;
	const auto ellipseFactor = 1.7f;

	const auto timeStep = quarter / 8;

	const auto fade = 0.3f;

	const auto scaleFactor = 8;
	const auto scaleMinimum = 8.0f;

	const auto colorOffset = 30;
	const auto colorOffset2 = colorOffset * 2;
	auto colors = std::vector<Color>({
		Color(0, 169,195),
		Color(0, 169 - colorOffset, 195 - colorOffset),
		Color(0, 169 - colorOffset2, 195 - colorOffset2),

		Color(247, 255, 8),
		Color(247 - colorOffset, 255 - colorOffset, 8),
		Color(247 - colorOffset2, 255 - colorOffset2, 8),

		Color(255, 209, 219),
		Color(255 - colorOffset, 209 - colorOffset, 219 - colorOffset),
		Color(255 - colorOffset2, 209 - colorOffset2, 219 - colorOffset2),

		Color(119, 255, 169),
		Color(119 - colorOffset, 255 - colorOffset, 169 - colorOffset),
		Color(119 - colorOffset2, 255 - colorOffset2, 169 - colorOffset2)
	});

	for (auto i = 0; i < numDots; ++i) {
		auto const sprite = Storyboard::CreateSprite("circle");
		sprite->Fade(startFadeIn, endFadeIn, 0.0f, fade, Easing::EasingIn);
		sprite->Fade(startFadeOut, endFadeOut, fade, 0.0f, Easing::EasingOut);

		for (auto i = startFadeIn; i < endFadeOut; i += timeStep) {
			Vector2 position;
			auto withinBounds = true;
			while (withinBounds) {
				const auto x = rand() % static_cast<int>(Vector2::ScreenSize.x) - Vector2::ScreenSize.x / 2;
				const auto y = rand() % static_cast<int>(Vector2::ScreenSize.y) - Vector2::ScreenSize.y / 2;
				const auto ellipse = Vector2(x / ellipseFactor, y);
				if (ellipse.Magnitude() > dotDistance) {
					withinBounds = false;
					position = Vector2(x, y);
				}
			}
			sprite->Move(i, i, position, position);

			const auto color = colors[rand() % colors.size()];
			sprite->Color(i, i, color, color);

			const auto scale = (rand() % scaleFactor + scaleMinimum) / imageWidth;
			sprite->Scale(i, i, scale, scale);
		}
	}
}

void setDotBackgrounds() {
	setDotBackground(62241, 65115, 67989, 69786);
	setDotBackground(274935, 277091, 279247, 280684);
}

void eyeSparkle() {
	const auto screenCenter = Vector2(-7, 15);
	const auto startSection = 273500;
	const auto endSection = 276000;
	const auto fade = 1.0f;
	const auto color = Color(255, 255, 255);
	auto scale = .01;
	auto scaleTips = Vector2(scale / 1.75, scale * 2.25);
	auto scaleBase = Vector2(scale, scale / 1.3);

	const auto position = Vector2(-7, 15);

	auto endScale = 1.0;
	auto endScaleTips = Vector2(endScale / 1.75, endScale * 2.25);
	auto endScaleBase = Vector2(endScale, endScale / 1.3);

	//250 x 200 y

	const auto xDelta = 100;
	const auto yDelta = 100;

	auto xDeltaRange = 7;
	auto yDeltaRange = 9;

	for (auto start = startSection; start < endSection; start += 100) {
		const auto end = start + 100;
		const auto centerxDelta = rand() % (xDeltaRange * 2 + 1) - xDeltaRange;
		const auto centeryDelta = rand() % 19 - 9;
		const auto position = Vector2(screenCenter.x + centerxDelta, screenCenter.y + centeryDelta);
		const auto xDelta = centerxDelta * 30;
		const auto yDelta = centeryDelta * 20;

		const auto center = Storyboard::CreateSprite("circle");
		Vector2 endPosition = Vector2(position.x + xDelta, position.y + yDelta);
		center->Move(start, end, position, endPosition, Easing::QuintIn);
		center->Color(start, start, color, color);
		center->Scale(start, end, scale, endScale, Easing::QuintIn);

		const auto top = Storyboard::CreateSprite("triangle");
		Vector2 positionTop = Vector2(position.x, position.y + 70 * scale);
		Vector2 endPositionTop = Vector2(position.x + xDelta, position.y + 70 * endScale + yDelta);
		top->Move(start, end, positionTop, endPositionTop, Easing::QuintIn);
		top->Color(start, start, color, color);
		top->ScaleVector(start, end, scaleTips, endScaleTips, Easing::QuintIn);

		const auto baseTop = Storyboard::CreateSprite("triangle");
		Vector2 posBaseTop = Vector2(position.x, position.y + 60 * scale);
		Vector2 endPosBaseTop = Vector2(position.x + xDelta, position.y + 60 * endScale + yDelta);
		baseTop->Move(start, end, posBaseTop, endPosBaseTop, Easing::QuintIn);
		baseTop->Color(start, start, color, color);
		baseTop->ScaleVector(start, end, scaleBase, endScaleBase, Easing::QuintIn);

		const auto bottom = Storyboard::CreateSprite("triangle");
		Vector2 positionBot = Vector2(position.x, position.y - 70 * scale);
		Vector2 endPositionBot = Vector2(position.x + xDelta, position.y - 70 * endScale + yDelta);
		bottom->Rotate(start, start, convertDegreesToRadians(180), convertDegreesToRadians(180));
		bottom->Move(start, end, positionBot, endPositionBot, Easing::QuintIn);
		bottom->Color(start, start, color, color);
		bottom->ScaleVector(start, end, scaleTips, endScaleTips, Easing::QuintIn);

		const auto baseBottom = Storyboard::CreateSprite("triangle");
		Vector2 posBaseBot = Vector2(position.x, position.y - 60 * scale);
		Vector2 endPosBaseBot = Vector2(position.x + xDelta, position.y - 60 * endScale + yDelta);
		baseBottom->Rotate(start, start, convertDegreesToRadians(180), convertDegreesToRadians(180));
		baseBottom->Move(start, end, posBaseBot, endPosBaseBot, Easing::QuintIn);
		baseBottom->Color(start, start, color, color);
		baseBottom->ScaleVector(start, end, scaleBase, endScaleBase, Easing::QuintIn);

		const auto right = Storyboard::CreateSprite("triangle");
		Vector2 positionRight = Vector2(position.x + 70 * scale, position.y);
		Vector2 endPositionRight = Vector2(position.x + 70 * endScale + xDelta, position.y + yDelta);
		right->Rotate(start, start, convertDegreesToRadians(90), convertDegreesToRadians(90));
		right->Move(start, end, positionRight, endPositionRight, Easing::QuintIn);
		right->Color(start, start, color, color);
		right->ScaleVector(start, end, scaleTips, endScaleTips, Easing::QuintIn);

		const auto baseRight = Storyboard::CreateSprite("triangle");
		Vector2 posBaseRight = Vector2(position.x + 60 * scale, position.y);
		Vector2 endPosBaseRight = Vector2(position.x + 60 * endScale + xDelta, position.y + yDelta);
		baseRight->Rotate(start, start, convertDegreesToRadians(90), convertDegreesToRadians(90));
		baseRight->Move(start, end, posBaseRight, endPosBaseRight, Easing::QuintIn);
		baseRight->Color(start, start, color, color);
		baseRight->ScaleVector(start, end, scaleBase, endScaleBase, Easing::QuintIn);

		const auto left = Storyboard::CreateSprite("triangle");
		Vector2 positionLeft = Vector2(position.x - 70 * scale, position.y);
		Vector2 endPositionLeft = Vector2(position.x - 70 * endScale + xDelta, position.y + yDelta);
		left->Rotate(start, start, convertDegreesToRadians(-90), convertDegreesToRadians(-90));
		left->Move(start, end, positionLeft, endPositionLeft, Easing::QuintIn);
		left->Color(start, start, color, color);
		left->ScaleVector(start, end, scaleTips, endScaleTips, Easing::QuintIn);

		const auto baseLeft = Storyboard::CreateSprite("triangle");
		Vector2 posBaseLeft = Vector2(position.x - 60 * scale, position.y);
		Vector2 endPosBaseLeft = Vector2(position.x - 60 * endScale + xDelta, position.y + yDelta);
		baseLeft->Rotate(start, start, convertDegreesToRadians(-90), convertDegreesToRadians(-90));
		baseLeft->Move(start, end, posBaseLeft, endPosBaseLeft, Easing::QuintIn);
		baseLeft->Color(start, start, color, color);
		baseLeft->ScaleVector(start, end, scaleBase, endScaleBase, Easing::QuintIn);
	}
}

void setBorder() {
	const auto borderOffset = 25.0f;
	const auto halfSize = Vector2::ScreenSize / 2;
	const auto color = Color(0.0f, 169.0f, 195.0f);
	const auto width = 10.0f;
	const auto horizontal = Vector2(Vector2::ScreenSize.x - 2 * borderOffset + width, width);
	const auto vertical = Vector2(width, Vector2::ScreenSize.y - 2 * borderOffset + width);

	auto const top = Storyboard::CreateSprite("pixel", Vector2(0.0f, halfSize.y - borderOffset));
	top->Color(29187, 29187, color, color);
	top->ScaleVector(29187, 30624, Vector2(width, width), horizontal, Easing::EasingIn);
	top->ScaleVector(65115, 70145, horizontal, Vector2(width, width), Easing::EasingOut);
	top->Fade(65115, 70145, 1, 0, Easing::EasingOut);

	top->ScaleVector(103738, 105354, Vector2(width, width), horizontal, Easing::EasingIn);
	top->Fade(103738, 105354, 0, 1, Easing::EasingIn);
	top->ScaleVector(145414, 150265, horizontal, Vector2(width, width), Easing::EasingOut);
	top->Fade(145414, 150265, 1, 0, Easing::EasingOut);

	top->ScaleVector(179187, 180444, Vector2(width, width), horizontal, Easing::EasingIn);
	top->Fade(179187, 180444, 0, 1, Easing::EasingIn);
	top->ScaleVector(200205, 203079, horizontal, Vector2(width, width), Easing::EasingOut);
	top->Fade(200205, 203079, 1, 0, Easing::EasingOut);

	top->ScaleVector(228947, 231103, Vector2(width, width), horizontal, Easing::EasingIn);
	top->Fade(228947, 231103, 0, 1, Easing::EasingIn);
	top->ScaleVector(279247, 280684, horizontal, Vector2(width, width), Easing::EasingOut);
	top->Fade(279247, 280684, 1, 0, Easing::EasingOut);

	auto const bottom = Storyboard::CreateSprite("pixel", Vector2(0.0f, -(halfSize.y - borderOffset)));
	bottom->Color(29187, 29187, color, color);
	bottom->ScaleVector(29187, 30624, Vector2(width, width), horizontal, Easing::EasingIn);
	bottom->ScaleVector(65115, 70145, horizontal, Vector2(width, width), Easing::EasingOut);
	bottom->Fade(65115, 70145, 1, 0, Easing::EasingOut);

	bottom->ScaleVector(103738, 105354, Vector2(width, width), horizontal, Easing::EasingIn);
	bottom->Fade(103738, 105354, 0, 1, Easing::EasingIn);
	bottom->ScaleVector(145414, 150265, horizontal, Vector2(width, width), Easing::EasingOut);
	bottom->Fade(145414, 150265, 1, 0, Easing::EasingOut);

	bottom->ScaleVector(179187, 180444, Vector2(width, width), horizontal, Easing::EasingIn);
	bottom->Fade(179187, 180444, 0, 1, Easing::EasingIn);
	bottom->ScaleVector(200205, 203079, horizontal, Vector2(width, width), Easing::EasingOut);
	bottom->Fade(200205, 203079, 1, 0, Easing::EasingOut);

	bottom->ScaleVector(228947, 231103, Vector2(width, width), horizontal, Easing::EasingIn);
	bottom->Fade(228947, 231103, 0, 1, Easing::EasingIn);
	bottom->ScaleVector(279247, 280684, horizontal, Vector2(width, width), Easing::EasingOut);
	bottom->Fade(279247, 280684, 1, 0, Easing::EasingOut);

	auto const right = Storyboard::CreateSprite("pixel", Vector2(-(halfSize.x - borderOffset), 0.0f));
	right->Color(29187, 29187, color, color);
	right->ScaleVector(29187, 30624, Vector2(width, width), vertical, Easing::EasingIn);
	right->ScaleVector(65115, 70145, vertical, Vector2(width, width), Easing::EasingOut);
	right->Fade(65115, 70145, 1, 0, Easing::EasingOut);

	right->ScaleVector(103738, 105354, Vector2(width, width), vertical, Easing::EasingIn);
	right->Fade(103738, 105354, 0, 1, Easing::EasingIn);
	right->ScaleVector(145414, 150265, vertical, Vector2(width, width), Easing::EasingOut);
	right->Fade(145414, 150265, 1, 0, Easing::EasingOut);

	right->ScaleVector(179187, 180444, Vector2(width, width), vertical, Easing::EasingIn);
	right->Fade(179187, 180444, 0, 1, Easing::EasingIn);
	right->ScaleVector(200205, 203079, vertical, Vector2(width, width), Easing::EasingOut);
	right->Fade(200205, 203079, 1, 0, Easing::EasingOut);

	right->ScaleVector(228947, 231103, Vector2(width, width), vertical, Easing::EasingIn);
	right->Fade(228947, 231103, 0, 1, Easing::EasingIn);
	right->ScaleVector(279247, 280684, vertical, Vector2(width, width), Easing::EasingOut);
	right->Fade(279247, 280684, 1, 0, Easing::EasingOut);

	auto const left = Storyboard::CreateSprite("pixel", Vector2(halfSize.x - borderOffset, 0.0f));
	left->Color(29187, 29187, color, color);
	left->ScaleVector(29187, 30624, Vector2(width, width), vertical, Easing::EasingIn);
	left->ScaleVector(65115, 70145, vertical, Vector2(width, width), Easing::EasingOut);
	left->Fade(65115, 70145, 1, 0, Easing::EasingOut);

	left->ScaleVector(103738, 105354, Vector2(width, width), vertical, Easing::EasingIn);
	left->Fade(103738, 105354, 0, 1, Easing::EasingIn);
	left->ScaleVector(145414, 150265, vertical, Vector2(width, width), Easing::EasingOut);
	left->Fade(145414, 150265, 1, 0, Easing::EasingOut);

	left->ScaleVector(179187, 180444, Vector2(width, width), vertical, Easing::EasingIn);
	left->Fade(179187, 180444, 0, 1, Easing::EasingIn);
	left->ScaleVector(200205, 203079, vertical, Vector2(width, width), Easing::EasingOut);
	left->Fade(200205, 203079, 1, 0, Easing::EasingOut);

	left->ScaleVector(228947, 231103, Vector2(width, width), vertical, Easing::EasingIn);
	left->Fade(228947, 231103, 0, 1, Easing::EasingIn);
	left->ScaleVector(279247, 280684, vertical, Vector2(width, width), Easing::EasingOut);
	left->Fade(279247, 280684, 1, 0, Easing::EasingOut);
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

	auto const bg = Storyboard::CreateSprite("pixel", Vector2::Zero, Layer::Background);
	bg->Scale(fadeStart, start, 0, horizontal.x, Easing::EasingIn);
	bg->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	bg->Scale(end, fadeEnd, horizontal.x, 0, Easing::EasingOut);
	bg->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);

	auto const top = Storyboard::CreateSprite("pixel", Vector2(0.0f, halfSize.y - borderOffset));
	top->Color(0, 0, color, color);
	top->ScaleVector(fadeStart, start, Vector2(width, width), horizontal, Easing::EasingIn);
	top->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	top->ScaleVector(end, fadeEnd, horizontal, Vector2(width, width), Easing::EasingOut);
	top->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);

	auto const bottom = Storyboard::CreateSprite("pixel", Vector2(0.0f, -(halfSize.y - borderOffset)));
	bottom->Color(0, 0, color, color);
	bottom->ScaleVector(fadeStart, start, Vector2(width, width), horizontal, Easing::EasingIn);
	bottom->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	bottom->ScaleVector(end, fadeEnd, horizontal, Vector2(width, width), Easing::EasingOut);
	bottom->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);

	auto const right = Storyboard::CreateSprite("pixel", Vector2(-(halfSize.x - borderOffset), 0.0f));
	right->Color(0, 0, color, color);
	right->ScaleVector(fadeStart, start, Vector2(width, width), vertical, Easing::EasingIn);
	right->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	right->ScaleVector(end, fadeEnd, vertical, Vector2(width, width), Easing::EasingOut);
	right->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);

	auto const left = Storyboard::CreateSprite("pixel", Vector2(halfSize.x - borderOffset, 0.0f));
	left->Color(0, 0, color, color);
	left->ScaleVector(fadeStart, start, Vector2(width, width), vertical, Easing::EasingIn);
	left->Fade(fadeStart, start, 0, 1, Easing::EasingIn);
	left->ScaleVector(end, fadeEnd, vertical, Vector2(width, width), Easing::EasingOut);
	left->Fade(end, fadeEnd, 1, 0, Easing::EasingOut);
}

S2VX::SpriteMoveCommand* getFirstS2VXMoveCommand(const std::vector<std::unique_ptr<S2VX::Command>>& commands) {
	for (const auto& command : commands) {
		const auto move = dynamic_cast<S2VX::SpriteMoveCommand*>(command.get());
		if (move != nullptr) {
			return move;
		}
	}
	return nullptr;
}

S2VX::SpriteRotateCommand* getFirstS2VXRotateCommand(const std::vector<std::unique_ptr<S2VX::Command>>& commands) {
	for (const auto& command : commands) {
		const auto rotate = dynamic_cast<S2VX::SpriteRotateCommand*>(command.get());
		if (rotate != nullptr) {
			return rotate;
		}
	}
	return nullptr;
}

S2VX::SpriteScaleCommand* getFirstS2VXScaleCommand(const std::vector<std::unique_ptr<S2VX::Command>>& commands) {
	for (const auto& command : commands) {
		const auto scale = dynamic_cast<S2VX::SpriteScaleCommand*>(command.get());
		if (scale != nullptr) {
			return scale;
		}
	}
	return nullptr;
}

S2VX::SpriteColorCommand* getFirstS2VXColorCommand(const std::vector<std::unique_ptr<S2VX::Command>>& commands) {
	for (const auto& command : commands) {
		const auto color = dynamic_cast<S2VX::SpriteColorCommand*>(command.get());
		if (color != nullptr) {
			return color;
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
		const auto ID = sprite->getTexture().getPath();
		const auto cameraValues = getCameraValuesAtMilliseconds(camera, sprite->getStart());
		const auto cameraScale = cameraValues.scale / imageWidth;
		const auto move = getFirstS2VXMoveCommand(sprite->getCommands());
		const auto center = convertCoordinatesToPosition(move->getStartCoordinate(), cameraValues);
		auto rotation = cameraValues.roll;
		const auto rotate = getFirstS2VXRotateCommand(sprite->getCommands());
		if (rotate) {
			rotation += convertDegreesToRadians(rotate->getStartRotation());
		}
		const auto color = getFirstS2VXColorCommand(sprite->getCommands());
		auto convertColor = Color();
		if (color) {
			convertColor = convertS2VXColorToOsuukiSBColor(color->getStartColor());
		}
		const auto scale = getFirstS2VXScaleCommand(sprite->getCommands());
		auto scaleValue = 0.8f;
		if (scale) {
			scaleValue = scale->getStartScale().x;
		}
		const auto spriteGroup = SpriteGroup(ID, imageWidth, move->getStart(), move->getEnd(), center, rotation, cameraScale, convertColor, quarter * 4, scaleValue);
		spriteBindings[i] = SpriteBinding{ S2VXSprites[i].get(), spriteGroup };
	}
	return spriteBindings;
}

void processS2VXSprites(S2VX::Camera& camera, const std::vector<SpriteBinding>& spriteBindings) {
	for (auto binding : spriteBindings) {
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
	// Reset camera
	camera.reset();
	camera.update(0);

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
				// Need to rotate to account for correct direction
				const auto scaleDistance = (convertDistance * cameraValues.scale).Rotate(camera.getRoll());
				for (auto sprite : spriteGroup.sprites) {
					// Minus to account for reverse
					const auto movePosition = sprite->position - scaleDistance;
					const auto parallaxEnd = end - rand() % moveParallax;
					sprite->Move(start, parallaxEnd, sprite->position, movePosition, easing);
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
					const auto parallaxEnd = end - rand() % moveParallax;
					const auto localRotatePosition = sprite->position.Rotate(rotation);
					sprite->Move(start, parallaxEnd, sprite->position, localRotatePosition, easing);
					sprite->Rotate(start, parallaxEnd, sprite->rotation, sprite->rotation + rotation, easing);
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
					const auto parallaxEnd = end - rand() % moveParallax;

					// Square
					if (sprite->scaleVector != Vector2(1.0f, 1.0f)) {
						sprite->ScaleVector(start, parallaxEnd, sprite->scaleVector, sprite->scaleVector * scale, easing);
					}
					// Circle
					else {
						sprite->Scale(start, parallaxEnd, sprite->scale, sprite->scale * scale, easing);
					}
					const auto localDifference = sprite->position - center;
					const auto localMagnitude = localDifference.Magnitude();
					const auto localNormalize = localDifference.Normalize();
					const auto spritePosition = scalePosition + localNormalize * (scale * localMagnitude);
					sprite->Move(start, parallaxEnd, sprite->position, spritePosition, easing);
				}
				spriteGroup.center = scalePosition;
				continue;
			}
		}
	}
}

void processScript(const std::string& path, Sprite* const bg) {
	S2VX::Display display;
	S2VX::Scripting scripting{ display };
	auto& elements = scripting.evaluate(path);
	processScriptBackground(elements.getBack(), bg);

	auto spriteBindings = createSpriteBindings(elements.getSprites().getSprites(), elements.getCamera());
	processS2VXSprites(elements.getCamera(), spriteBindings);
	processCamera(elements.getCamera(), spriteBindings);

	// Handle endings of sprite bindings
	// For shape video sections we're gonna have some hacks so that the makeShapeVideo can just handle it directly
	if (path == "guitarSolo.chai" || path == "anime.chai") {
		return;
	}
	for (auto i = 0; i < spriteBindings.size(); ++i) {
		// Specially handle screenShots script so that it doesn't waste commands exploding under new screenshots
		if (path == "screenShots.chai") {
			if (i == spriteBindings.size() - 1) {
				spriteBindings[i].spriteGroup.explode();
			}
			else {
				spriteBindings[i].spriteGroup.clear();
			}
		}
		else {
			spriteBindings[i].spriteGroup.explode();
		}
	}
}

int main() {
		srand(time(NULL));

		auto const hideBackground = Storyboard::CreateSprite("bg.jpg", Vector2::Zero, Layer::Background);
		auto const bg = Storyboard::CreateSprite("pixel", Vector2::Zero, Layer::Background);
		// For testing
		//bg->ScaleVector(0, 300000, Vector2::ScreenSize, Vector2::ScreenSize);

		processBackground(bg);
		processScript("lyrics.chai", bg);
		//processScript("faces.chai", bg);
		//processScript("instruments.chai", bg);
		//processScript("screenShots.chai", bg);
		//processScript("swing.chai", bg);
		//processScript("guitarSolo.chai", bg);

		//processScript("musicSheet.chai", bg);
		//MusicSheet("voice.MusicSheet", 122, imageWidth, Color(0, 169, 195), "lyric.MusicSheet", false);
		//MusicSheet("wind.MusicSheet", 0, imageWidth, Color(247, 255, 8), "", true);
		//MusicSheet("drum.MusicSheet", -140, imageWidth, Color(255, 209, 219), "", false);

		processScript("anime.chai", bg);
		//processScript("animeBorders.chai", bg);

		setDotBackgrounds();

		eyeSparkle();

		// Blue line rectangle border
		setBorder();

		// Logo
		//setS2VXBorder();

		auto storyboardInputPath = std::ifstream("StoryboardInputPath.txt");
		std::string path;
		std::getline(storyboardInputPath, path);
		Storyboard::Write(path);
	return 0;
}