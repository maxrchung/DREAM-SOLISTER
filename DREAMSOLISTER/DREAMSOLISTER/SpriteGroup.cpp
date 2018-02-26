#include "SpriteGroup.hpp"
#include <algorithm>

SpriteGroup::SpriteGroup(const std::string& path, const int pImageWidth, const int pStart, const int pEnd, const Vector2& pCenter, const float pRotation, const float pScale, const int pOffset)
	: imageWidth{ pImageWidth }, start{ pStart }, end{ pEnd }, center{ pCenter }, rotation{ pRotation }, scale{ pScale }, lineHeight{ 7.0f * pScale }, overallScale{ 0.8f }, offset{ pOffset } {
	if (path == "A") {
		makeSpriteGroup({
			-1,-1,	-1,1,
			-1,1,	1,1,
			1,1,	1,-1,
			-1,0,	1,0
		});
	}
	else if (path == "E") {
		makeSpriteGroup({
			-1,1,	-1,-1,
			-1,1,	1,1,
			-1,0,	1,0,
			-1,-1,	1,-1
		});
	}
	else if (path == "I") {
		makeSpriteGroup({
			-1,1,	1,1,
			0,1,	0,-1,
			-1,-1,	1,-1
		});
	}
	else if (path == "K") {
		makeSpriteGroup({
			-1,1,	-1,-1,
			1,1,	-1,0,
			-1,0,	1,-1
		});
	}
	else if (path == "N") {
		makeSpriteGroup({
			-1,1,	-1,-1,
			-1,1,	1,-1,
			1,1,	1,-1
		});
	}
	else if (path == "T") {
		makeSpriteGroup({
			-1,1,	1,1,
			0,1,	0,-1
		});
	}
	else {
		sprites = { new Sprite(path, center) };
	}
}

void SpriteGroup::makeSpriteGroup(const std::vector<float>& points) {
	auto scalePoints = points;
	std::for_each(scalePoints.begin(), scalePoints.end(), [=](float& point) { point *= scale * overallScale * imageWidth / 2; });
	const auto scaleHeight = lineHeight * overallScale / imageWidth;

	for (auto i = 0; i < scalePoints.size(); i += 4) {
		const auto startFade = start - offset;

		const auto startPoint = center + Vector2(scalePoints[i], scalePoints[i + 1]).Rotate(rotation);
		const auto endPoint = center + Vector2(scalePoints[i + 2], scalePoints[i + 3]).Rotate(rotation);
		const auto midPoint = (startPoint + endPoint) / 2.0f;

		auto sprite = new Sprite("square.png", midPoint);
		sprite->Fade(startFade, start, 0, 1.0f);

		const auto direction = rand() % 360;
		const auto startPosition = midPoint + Vector2(scale * overallScale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);

		sprite->Move(startFade, start, startPosition, midPoint);
		const auto difference = endPoint - startPoint;
		const auto angleBetween = Vector2(1.0f, 0.0).AngleBetween(difference);
		sprite->Rotate(startFade, start, 0, angleBetween);

		const auto distance = difference.Magnitude();
		const auto scaleWidth = distance / imageWidth;
		const auto spriteScale = Vector2(scaleWidth, scaleHeight);
		sprite->ScaleVector(startFade, start, Vector2(scaleHeight, scaleHeight), spriteScale);
		sprites.push_back(sprite);
	}
}