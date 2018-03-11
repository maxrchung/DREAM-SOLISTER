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
	if (path == "A") {
		makeGridSpriteGroup({
			-1,-1,	-1,1,
			-1,1,	1,1,
			1,1,	1,-1,
			-1,0,	1,0
		}, {
			-1,-1,
			-1,1,
			1,1,
			1,-1
		});
	}
	else if (path == "B") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,1,	0,1,
			0,1,	1,0.5,
			1,0.5,	0,0,
			0,0,	-1,0,
			0,0,	1,-0.5,
			1,-0.5,	0,-1,
			0,-1,	-1,-1
		}, {
			-1,1,
			-1,-1,
			0,1,
			1,0.5,
			1,-0.5,
			0,-1,
		});
	}
	else if (path == "C") {
		makeGridSpriteGroup({
			1,1,	-1,1,
			-1,1,	-1,-1,
			-1,-1,	1,-1
		}, {
			1,1,
			-1,1,
			-1,-1,
			1,-1
		});
	}
	else if (path == "D") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,1,	0,1,
			0,1,	1,0,
			1,0,	0,-1,
			0,-1,	-1,-1
		}, {
			-1,1,
			0,1,
			1,0,
			0,-1,
			-1,-1
		});
	}
	else if (path == "E") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,1,	1,1,
			-1,0,	1,0,
			-1,-1,	1,-1
		}, {
			-1,1,
			-1,-1,
			1,1,
			1,0,
			1,-1
		});
	}
	else if (path == "F") {
		makeGridSpriteGroup({
			-1,1,	1,1,
			-1,1,	-1,-1,
			-1,0,	1,0,
		}, {
			-1,1,
			1,1,
			-1,-1,
			1,0
		});
	}
	else if (path == "G") {
		makeGridSpriteGroup({
			1,1,	-1,1,
			-1,1,	-1,-1,
			-1,-1,	1,-1,
			1,-1,	1,0,
			1,0,	0,0
		}, {
			1,1,
			-1,1,
			-1,-1,
			1,-1,
			1,0,
			0,0
		});
	}
	else if (path == "H") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,0,	1,0,
			1,1,	1,-1,
		}, {
			-1,1,
			-1,-1,
			1,1,
			1,-1
		});
	}
	else if (path == "I") {
		makeGridSpriteGroup({
			-1,1,	1,1,
			0,1,	0,-1,
			-1,-1,	1,-1
		}, {
			-1,1,
			1,1,
			-1,-1,
			1,-1
		});
	}
	else if (path == "K") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			1,1,	-1,0,
			-1,0,	1,-1
		}, {
			-1,1,
			-1,-1,
			1,1,
			1,-1
		});
	}
	else if (path == "M") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,1,	0,0,
			0,0,	1,1,
			1,1,	1,-1
		}, {
			-1,1,
			-1,-1,
			0,0,
			1,1,
			1,-1
		});
	}
	else if (path == "N") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,1,	1,-1,
			1,1,	1,-1
		}, {
			-1,1,
			-1,-1,
			1,1,
			1,-1
		});
	}
	else if (path == "O") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,-1,	1,-1,
			1,-1,	1,1,
			1,1,	-1,1
		}, {
			-1,1,
			-1,-1,
			1,-1,
			1,1
		});
	}
	else if (path == "R") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,1,	1,1,
			1,1,	1,0,
			1,0,	-1,0,
			-1,0,	1,-1
		}, {
			-1,1,
			-1,-1,
			1,1,
			1,0,
			1,-1
		});
	}
	else if (path == "S") {
		makeGridSpriteGroup({
			1,1,	-1,1,
			-1,1,	-1,0,
			-1,0,	1,0,
			1,0,	1,-1,
			1,-1,	-1,-1
		}, {
			1,1,
			-1,1,
			-1,0,
			1,0,
			1,-1,
			-1,-1
		});
	}
	else if (path == "T") {
		makeGridSpriteGroup({
			-1,1,	1,1,
			0,1,	0,-1
		}, {
			-1,1,
			1,1,
			0,-1
		});
	}
	else if (path == "U") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,-1,	1,-1,
			1,-1,	1,1
		}, {
			-1,1,
			-1,-1,
			1,-1,
			1,1
		});
	}
	else if (path == "V") {
		makeGridSpriteGroup({
			-1,1,	0,-1,
			0,-1,	1,1
		}, {
			-1,1,
			0,-1,
			1,1
		});
	}
	else if (path == "W") {
		makeGridSpriteGroup({
			-1,1,	-1,-1,
			-1,-1,	0,0,
			0,0,	1,-1,
			1,-1,	1,1
		}, {
			-1,1,
			-1,-1,
			0,0,
			1,-1,
			1,1
		});
	}
	else if (path == "X") {
		makeGridSpriteGroup({
			-1,1,	1,-1,
			1,1,	-1,-1
		}, {
			-1,1,
			1,-1,
			1,1,
			-1,-1
		});
	}
	else if (path == "Y") {
		makeGridSpriteGroup({
			-1,1,	0,0,
			1,1,	0,0,
			0,0,	0,-1
		}, {
			-1,1,
			1,1,
			0,-1
		});
	}
	else if (path == "2") {
		makeGridSpriteGroup({
			-1,1,	1,1,
			1,1,	1,0,
			1,0,	-1,0,
			-1,0,	-1,-1,
			-1,-1,	1,-1
		}, {
			-1,1,
			1,1,
			1,0,
			-1,0,
			-1,-1,
			1,-1
		});
	}
	else if (path == "!!!") {
		makeGridSpriteGroup({
			-1,1,	-1,0,
			0,1,	0,0,
			1,1,	1,0
		}, {
			-1,1,
			-1,0,
			-1,-1,
			0,1,
			0,0,
			0,-1,
			1,1,
			1,0,
			1,-1
		});
	}
	else if (path == "MusicNote") {
		makeMusicNote();
	}
	else {
		sprites = { new Sprite(path, center) };
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

void SpriteGroup::makeGridSpriteGroup(const std::vector<float>& linePoints, const std::vector<float>& points) {
	// Perform a copy so we can format in constructor easier
	auto scaledLinePoints = linePoints;
	const auto scaleHeight = lineHeight * overallScale / imageWidth;

	// The fuck am I doing
	// https://stackoverflow.com/questions/18006685/call-a-member-function-using-for-each
	auto scalePointFunction = std::bind(&SpriteGroup::scalePoint, this, std::placeholders::_1);
	std::for_each(scaledLinePoints.begin(), scaledLinePoints.end(), scalePointFunction);

	for (auto i = 0; i < scaledLinePoints.size(); i += 4) {
		const auto startPoint = center + Vector2(scaledLinePoints[i], scaledLinePoints[i + 1]).Rotate(rotation);
		const auto endPoint = center + Vector2(scaledLinePoints[i + 2], scaledLinePoints[i + 3]).Rotate(rotation);
		const auto midPoint = (startPoint + endPoint) / 2.0f;

		auto const sprite = new Sprite("square.png", midPoint);
		sprite->Color(startFade, startFade, color, color);
		sprite->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);

		const auto direction = rand() % 360;
		const auto startPosition = midPoint + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);
		sprite->Move(startFade, start, startPosition, midPoint, Easing::EasingIn);
		const auto difference = endPoint - startPoint;
		const auto angleBetween = Vector2(1.0f, 0.0).AngleBetween(difference);
		sprite->Rotate(startFade, start, 0, angleBetween, Easing::EasingIn);

		const auto distance = difference.Magnitude();
		const auto scaleWidth = distance / imageWidth;
		const auto spriteScale = Vector2(scaleWidth, scaleHeight);
		sprite->ScaleVector(startFade, start, Vector2(scaleHeight, scaleHeight), spriteScale, Easing::EasingIn);
		sprites.push_back(sprite);
	}

	auto scaledPoints = points;
	const auto pointWidth = scaleHeight * circleScale;
	std::for_each(scaledPoints.begin(), scaledPoints.end(), scalePointFunction);
	for (auto i = 0; i < scaledPoints.size(); i += 2) {
		const auto startFade = start - offset;
		const auto position = center + Vector2(scaledPoints[i], scaledPoints[i + 1]).Rotate(rotation);

		auto const sprite = new Sprite("circle.png", position);
		sprite->Color(startFade, startFade, color, color);
		sprite->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);

		const auto direction = rand() % 360;
		const auto startPosition = position + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);
		sprite->Move(startFade, start, startPosition, position, Easing::EasingIn);

		sprite->Scale(startFade, start, pointWidth, pointWidth);
		sprites.push_back(sprite);
	}
}

void SpriteGroup::makeMusicNote() {
	const auto scaleHeight = lineHeight * overallScale / imageWidth * noteLineScale;

	auto linePoints = noteLinePoints;
	auto scalePointFunction = std::bind(&SpriteGroup::scalePoint, this, std::placeholders::_1);
	std::for_each(linePoints.begin(), linePoints.end(), scalePointFunction);

	const auto startPoint = center + Vector2(linePoints[0], linePoints[1]).Rotate(rotation);
	const auto endPoint = center + Vector2(linePoints[2], linePoints[3]).Rotate(rotation);
	const auto midPoint = (startPoint + endPoint) / 2.0f;

	auto const sprite = new Sprite("square.png", midPoint);
	sprite->Color(startFade, startFade, color, color);
	sprite->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);

	const auto direction = rand() % 360;
	const auto startPosition = midPoint + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);
	sprite->Move(startFade, start, startPosition, midPoint, Easing::EasingIn);
	const auto difference = endPoint - startPoint;
	const auto angleBetween = Vector2(1.0f, 0.0).AngleBetween(difference);
	sprite->Rotate(startFade, start, 0, angleBetween, Easing::EasingIn);

	const auto distance = difference.Magnitude();
	const auto scaleWidth = distance / imageWidth;
	const auto spriteScale = Vector2(scaleWidth, scaleHeight);
	sprite->ScaleVector(startFade, start, Vector2(scaleHeight, scaleHeight), spriteScale, Easing::EasingIn);
	sprites.push_back(sprite);

	auto point = notePoint;
	const auto noteScale = notePointScale * scaleHeight;
	std::for_each(point.begin(), point.end(), scalePointFunction);
	const auto position = center + Vector2(notePoint[0], notePoint[1]).Rotate(rotation);

	auto const note = new Sprite("circle.png", position);
	note->Color(startFade, startFade, color, color);
	note->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);;
	note->Rotate(startFade, start, 0, rotation + noteRotation, Easing::EasingIn);
	note->Move(startFade, start, startPosition, position, Easing::EasingIn);
	note->ScaleVector(startFade, start, Vector2(noteScale.y, noteScale.y), noteScale);
	sprites.push_back(note);
}

void SpriteGroup::scalePoint(float& value) {
	value *= scale * overallScale * imageWidth / 2;
}