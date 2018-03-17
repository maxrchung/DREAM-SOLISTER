#include "SpriteGroup.hpp"
#include <algorithm>

const float SpriteGroup::circleScale = 2.0f;
const std::vector<float> SpriteGroup::noteLinePoints = std::vector<float>({ 0.19f,0.75f,	0.19f,-0.5f });
const float SpriteGroup::noteRotation = -25 * 3.14159f / 180.0f;
const float SpriteGroup::noteLineScale = 0.7f;
const std::vector<float> SpriteGroup::notePoint = std::vector<float>({ 0.0f,-0.5f });
const Vector2 SpriteGroup::notePointScale = Vector2(5.1f, 4.0f);

SpriteGroup::SpriteGroup(const std::string& path, const int pImageWidth, const int pStart, const int pEnd, const Vector2& pCenter, const float pRotation, const float pScale, const Color pColor, const int pOffset)
	: imageWidth{ pImageWidth }, 
	start{ pStart }, 
	end{ pEnd }, 
	center{ pCenter }, 
	rotation{ pRotation }, 
	scale{ pScale }, 
	lineHeight{ 7.0f * pScale }, 
	overallScale{ 0.8f }, 
	color{ pColor }, 
	offset{ pOffset },
	startFade{ pStart - pOffset } {
	const auto linePoints = LinePoints(path);
	if (linePoints.isEmpty()) {
		if (path == "MusicNote") {
			makeMusicNote();
		}
		else {
			sprites = { new Sprite(path, center) };
		}
	}
	else {
		makeLinePoints(linePoints);
	}
}

void SpriteGroup::destroy() {
	for (auto sprite : sprites) {
		auto endFade = end + offset;
		sprite->Fade(end, endFade, 1.0f, 0.0f);

		const auto direction = rand() % 360;
		const auto endPosition = sprite->position + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);
		sprite->Move(end, endFade, sprite->position, endPosition, Easing::EasingOut);

		// Readjust scale vector
		if (sprite->scaleVector != Vector2(1.0f, 1.0f)) {
			auto min = std::min(sprite->scaleVector.x, sprite->scaleVector.y);
			sprite->ScaleVector(end, endFade, sprite->scaleVector, Vector2(min, min), Easing::EasingOut);
		}

		sprite->Rotate(end, endFade, sprite->rotation, 0, Easing::EasingOut);
	}
}

void SpriteGroup::makeLine(float x1, float y1, float x2, float y2, float scaleHeight) {
	const auto startPoint = center + Vector2(x1, y1).Rotate(rotation);
	const auto endPoint = center + Vector2(x2, y2).Rotate(rotation);
	const auto midPoint = (startPoint + endPoint) / 2.0f;
	const auto difference = endPoint - startPoint;
	const auto distance = difference.Magnitude();
	const auto angleBetween = Vector2(1.0f, 0.0).AngleBetween(difference);
	const auto scaleWidth = distance / imageWidth;
	const auto spriteScale = Vector2(scaleWidth, scaleHeight);
	const auto direction = rand() % 360;
	const auto startPosition = midPoint + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);

	auto const sprite = new Sprite("square", midPoint);
	sprite->Color(startFade, startFade, color, color);
	sprite->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);
	sprite->Move(startFade, start, startPosition, midPoint, Easing::EasingIn);
	sprite->Rotate(startFade, start, 0, angleBetween, Easing::EasingIn);
	sprite->ScaleVector(startFade, start, Vector2(scaleHeight, scaleHeight), spriteScale, Easing::EasingIn);
	sprites.push_back(sprite);
}

void SpriteGroup::makePoint(float x, float y, float pointWidth) {
	const auto startFade = start - offset;
	const auto position = center + Vector2(x, y).Rotate(rotation);
	const auto direction = rand() % 360;
	const auto startPosition = position + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);

	auto const sprite = new Sprite("circle", position);
	sprite->Color(startFade, startFade, color, color);
	sprite->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);
	sprite->Move(startFade, start, startPosition, position, Easing::EasingIn);
	sprite->Scale(startFade, start, pointWidth, pointWidth);
	sprites.push_back(sprite);
}

void SpriteGroup::makeLinePoints(const LinePoints& linePoints) {
	// Perform a copy so we can format in constructor easier
	auto scaledLinePoints = linePoints.lines;
	const auto scaleHeight = lineHeight * overallScale / imageWidth;

	// The fuck am I doing
	// https://stackoverflow.com/questions/18006685/call-a-member-function-using-for-each
	auto scalePointFunction = std::bind(&SpriteGroup::scalePoint, this, std::placeholders::_1);
	std::for_each(scaledLinePoints.begin(), scaledLinePoints.end(), scalePointFunction);

	for (auto i = 0; i < scaledLinePoints.size(); i += 4) {
		makeLine(scaledLinePoints[i], scaledLinePoints[i + 1], scaledLinePoints[i + 2], scaledLinePoints[i + 3], scaleHeight);
	}

	auto scaledPoints = linePoints.points;
	const auto pointWidth = scaleHeight * circleScale;
	std::for_each(scaledPoints.begin(), scaledPoints.end(), scalePointFunction);
	for (auto i = 0; i < scaledPoints.size(); i += 2) {
		makePoint(scaledPoints[i], scaledPoints[i + 1], pointWidth);
	}
}

void SpriteGroup::makeNote(float x, float y, const Vector2& noteScale) {
	const auto position = center + Vector2(x, y).Rotate(rotation);
	const auto direction = rand() % 360;
	const auto startPosition = position + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);

	auto const note = new Sprite("circle", position);
	note->Color(startFade, startFade, color, color);
	note->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);;
	note->Rotate(startFade, start, 0, rotation + noteRotation, Easing::EasingIn);

	note->Move(startFade, start, startPosition, position, Easing::EasingIn);
	note->ScaleVector(startFade, start, Vector2(noteScale.y, noteScale.y), noteScale);
	sprites.push_back(note);
}

void SpriteGroup::makeMusicNote() {
	const auto scaleHeight = lineHeight * overallScale / imageWidth * noteLineScale;

	auto linePoints = noteLinePoints;
	auto scalePointFunction = std::bind(&SpriteGroup::scalePoint, this, std::placeholders::_1);
	std::for_each(linePoints.begin(), linePoints.end(), scalePointFunction);
	makeLine(linePoints[0], linePoints[1], linePoints[2], linePoints[3], scaleHeight);

	auto point = notePoint;
	const auto noteScale = notePointScale * scaleHeight;
	std::for_each(point.begin(), point.end(), scalePointFunction);
	makeNote(point[0], point[1], noteScale);
}

void SpriteGroup::scalePoint(float& value) {
	value *= scale * overallScale * imageWidth / 2;
}