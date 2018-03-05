#include "SpriteGroup.hpp"
#include <algorithm>

SpriteGroup::SpriteGroup(const std::string& path, const int pImageWidth, const int pStart, const int pEnd, const Vector2& pCenter, const float pRotation, const float pScale, const Color pColor, const int pOffset)
	: imageWidth{ pImageWidth }, start{ pStart }, end{ pEnd }, center{ pCenter }, rotation{ pRotation }, scale{ pScale }, lineHeight{ 7.0f * pScale }, circleScale{ 2.0f }, overallScale{ 0.8f }, color{ pColor }, offset{ pOffset } {
	if (path == "A") {
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
			-1,1,	1,1,
			0,1,	0,-1
		}, {
			-1,1,
			1,1,
			0,-1
		});
	}
	else if (path == "U") {
		makeSpriteGroup({
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
		makeSpriteGroup({
			-1,1,	0,-1,
			0,-1,	1,1
		}, {
			-1,1,
			0,-1,
			1,1
		});
	}
	else if (path == "W") {
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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
		makeSpriteGroup({
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

		// Square
		if (sprite->scaleVector != Vector2(1.0f, 1.0f)) {
			auto min = std::min(sprite->scaleVector.x, sprite->scaleVector.y);
			sprite->ScaleVector(end, endFade, sprite->scaleVector, Vector2(min, min), Easing::EasingOut);
		}

		sprite->Rotate(end, endFade, sprite->rotation, 0, Easing::EasingOut);
	}
}

void SpriteGroup::makeSpriteGroup(const std::vector<float>& linePoints, const std::vector<float>& points) {
	// Perform a copy so we can format in constructor easier
	auto scaledLinePoints = linePoints;
	const auto scaleHeight = lineHeight * overallScale / imageWidth;

	// The fuck am I doing
	// https://stackoverflow.com/questions/18006685/call-a-member-function-using-for-each
	auto scalePointFunction = std::bind(&SpriteGroup::scalePoint, this, std::placeholders::_1);
	std::for_each(scaledLinePoints.begin(), scaledLinePoints.end(), scalePointFunction);

	const auto startFade = start - offset;
	for (auto i = 0; i < scaledLinePoints.size(); i += 4) {
		const auto startPoint = center + Vector2(scaledLinePoints[i], scaledLinePoints[i + 1]).Rotate(rotation);
		const auto endPoint = center + Vector2(scaledLinePoints[i + 2], scaledLinePoints[i + 3]).Rotate(rotation);
		const auto midPoint = (startPoint + endPoint) / 2.0f;

		auto sprite = new Sprite("square.png", midPoint);
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

		auto sprite = new Sprite("circle.png", position);
		sprite->Color(startFade, startFade, color, color);
		sprite->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);

		const auto direction = rand() % 360;
		const auto startPosition = position + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);
		sprite->Move(startFade, start, startPosition, position, Easing::EasingIn);

		sprite->Scale(startFade, start, pointWidth, pointWidth);
		sprites.push_back(sprite);
	}
}

void SpriteGroup::scalePoint(float& value) {
	value *= scale * overallScale * imageWidth / 2;
}