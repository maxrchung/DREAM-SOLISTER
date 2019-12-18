#include "SpriteGroup.hpp"
#include "S2RYBRUH/Storyboard.hpp"
#include <algorithm>

const float SpriteGroup::circleScale = 2.0f;
const std::vector<float> SpriteGroup::noteLinePoints = std::vector<float>({ 0.19f,0.75f,	0.19f,-0.5f });
const float SpriteGroup::noteRotation = -25 * 3.14159f / 180.0f;
const float SpriteGroup::noteLineScale = 0.7f;
const std::vector<float> SpriteGroup::notePoint = std::vector<float>({ 0.0f,-0.5f });
const Vector2 SpriteGroup::notePointScale = Vector2(5.1f, 4.0f);
const float SpriteGroup::startScaleLimit = 0.25f;

SpriteGroup::SpriteGroup(const std::string& ID, const int pImageWidth, const int pStart, const int pEnd, const Vector2& pCenter, const float pRotation, const float pCameraScale, const Color pColor, const int pOffset, const float pScale)
	: imageWidth{ pImageWidth }, 
	start{ pStart }, 
	end{ pEnd }, 
	center{ pCenter }, 
	rotation{ pRotation }, 
	cameraScale{ pCameraScale },
	lineHeight{ 7.0f * pCameraScale },
	scale{ pScale }, 
	color{ pColor }, 
	offset{ pOffset },
	startOffset{ pStart - pOffset },
	startScale{ lineHeight * scale / imageWidth },
	endOffset{ pEnd + pOffset } {
	const auto shapeAnimation = ShapeAnimation(ID);
	if (!shapeAnimation.isEmpty()) {
		makeShapeAnimation(shapeAnimation);
		return;
	}

	const auto linePoints = LinePoints(ID);
	if (linePoints.isEmpty()) {
		// Specially handle music note
		if (ID == "MusicNote") {
			makeMusicNote();
		}
		else {
			sprites = { Storyboard::CreateSprite(ID, center) };
		}
	}
	else {
		makeLinePoints(linePoints);
	}
}

void SpriteGroup::clear() {
	// Ideally we don't have to do this, but due to (I think) mistimings with our 
	// sprite movements to camera movements (that I don't want to look into), we
	// need to explicitly tell these sprites to go away.
	for (auto sprite : sprites) {
		sprite->Fade(end, end, 0.0f, 0.0f);
	}
}

void SpriteGroup::explode() {
	for (auto sprite : sprites) {
		sprite->Fade(end, endOffset, 1.0f, 0.0f);

		const auto direction = rand() % 360;
		const auto endPosition = sprite->position + Vector2(cameraScale * scale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);
		sprite->Move(end, endOffset, sprite->position, endPosition, Easing::EasingOut);

		// Readjust scale vector
		if (sprite->scaleVector != Vector2(1.0f, 1.0f)) {
			auto min = std::min(sprite->scaleVector.x, sprite->scaleVector.y);
			// Limit this for shape animation
			min = min > startScaleLimit ? startScaleLimit : min;
			sprite->ScaleVector(end, endOffset, sprite->scaleVector, Vector2(min, min), Easing::EasingOut);
		}

		sprite->Rotate(end, endOffset, sprite->rotation, 0, Easing::EasingOut);
	}
}

void SpriteGroup::makeShapeAnimation(const ShapeAnimation& shapeAnimation) {
	for (const auto& shape : shapeAnimation.shapes) {
		std::string path;
		switch (shape.type) {
			case ShapeType::Ellipse:
				path = "circle.png";
				break;
			case ShapeType::Rectangle:
				path = "square.png";
				break;
			case ShapeType::Semicircle:
				path = "semicircle.png";
				break;
			case ShapeType::Triangle:
				path = "triangle.png";
				break;
		}

		// Limit startScale to a quarter scale
		startScale = startScale > startScaleLimit ? startScaleLimit : startScale;
		const auto scaledPosition = shape.position * cameraScale * scale * imageWidth;
		const auto position = center + scaledPosition.Rotate(rotation);
		const auto direction = rand() % 360;
		const auto startPosition = position + Vector2(cameraScale * scale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);
		const auto endScale = Vector2(shape.scaleVector) * imageWidth / 900.0f * cameraScale * scale;

		auto const sprite = Storyboard::CreateSprite(path);
		sprite->Color(startOffset, startOffset, shape.color, shape.color);
		sprite->Fade(startOffset, start, 0, 1.0f, Easing::EasingIn);
		sprite->Move(startOffset, start, startPosition, position, Easing::EasingIn);
		sprite->Rotate(startOffset, start, 0, shape.rotation + rotation, Easing::EasingIn);
		sprite->ScaleVector(startOffset, start, Vector2(startScale, startScale), endScale, Easing::EasingIn);
		sprites.push_back(sprite);
	}
}

void SpriteGroup::makeLine(const float x1, const float y1, const float x2, const float y2, const float scaleHeight) {
	const auto startPoint = center + Vector2(x1, y1).Rotate(rotation);
	const auto endPoint = center + Vector2(x2, y2).Rotate(rotation);
	const auto midPoint = (startPoint + endPoint) / 2.0f;
	const auto difference = endPoint - startPoint;
	const auto distance = difference.Magnitude();
	const auto angleBetween = Vector2(1.0f, 0.0).AngleBetween(difference);
	const auto scaleWidth = distance / imageWidth;
	const auto endScale = Vector2(scaleWidth, startScale);
	const auto direction = rand() % 360;
	const auto startPosition = midPoint + Vector2(cameraScale * scale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);

	auto const sprite = Storyboard::CreateSprite("square", midPoint);
	sprite->Color(startOffset, startOffset, color, color);
	sprite->Fade(startOffset, start, 0, 1.0f, Easing::EasingIn);
	sprite->Move(startOffset, start, startPosition, midPoint, Easing::EasingIn);
	sprite->Rotate(startOffset, start, 0, angleBetween, Easing::EasingIn);
	sprite->ScaleVector(startOffset, start, Vector2(scaleHeight, scaleHeight), endScale, Easing::EasingIn);
	sprites.push_back(sprite);
}

void SpriteGroup::makePoint(const float x, const float y, const float pointWidth) {
	const auto startFade = start - offset;
	const auto position = center + Vector2(x, y).Rotate(rotation);
	const auto direction = rand() % 360;
	const auto startPosition = position + Vector2(cameraScale * scale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);

	auto const sprite = Storyboard::CreateSprite("circle", position);
	sprite->Color(startFade, startFade, color, color);
	sprite->Fade(startFade, start, 0, 1.0f, Easing::EasingIn);
	sprite->Move(startFade, start, startPosition, position, Easing::EasingIn);
	sprite->Scale(startFade, start, pointWidth, pointWidth);
	sprites.push_back(sprite);
}

void SpriteGroup::makeLinePoints(const LinePoints& linePoints) {
	// Perform a copy so we can format in constructor easier
	auto scaledLinePoints = linePoints.lines;

	// The fuck am I doing
	// https://stackoverflow.com/questions/18006685/call-a-member-function-using-for-each
	auto scalePointFunction = std::bind(&SpriteGroup::scalePoint, this, std::placeholders::_1);
	std::for_each(scaledLinePoints.begin(), scaledLinePoints.end(), scalePointFunction);

	for (auto i = 0; i < scaledLinePoints.size(); i += 4) {
		makeLine(scaledLinePoints[i], scaledLinePoints[i + 1], scaledLinePoints[i + 2], scaledLinePoints[i + 3], startScale);
	}

	auto scaledPoints = linePoints.points;
	const auto pointWidth = startScale * circleScale;
	std::for_each(scaledPoints.begin(), scaledPoints.end(), scalePointFunction);
	for (auto i = 0; i < scaledPoints.size(); i += 2) {
		makePoint(scaledPoints[i], scaledPoints[i + 1], pointWidth);
	}
}

void SpriteGroup::makeNote(const float x, const float y, const Vector2& noteScale) {
	const auto position = center + Vector2(x, y).Rotate(rotation);
	const auto direction = rand() % 360;
	const auto startPosition = position + Vector2(cameraScale * scale * imageWidth, 0.0f).Rotate(direction * 3.14159f / 180.0f);

	auto const note = Storyboard::CreateSprite("circle", position);
	note->Color(startOffset, startOffset, color, color);
	note->Fade(startOffset, start, 0, 1.0f, Easing::EasingIn);;
	note->Rotate(startOffset, start, 0, rotation + noteRotation, Easing::EasingIn);

	note->Move(startOffset, start, startPosition, position, Easing::EasingIn);
	note->ScaleVector(startOffset, start, Vector2(noteScale.y, noteScale.y), noteScale);
	sprites.push_back(note);
}

void SpriteGroup::makeMusicNote() {
	const auto scaleHeight = lineHeight * scale / imageWidth * noteLineScale;

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
	value *= cameraScale * scale * imageWidth / 2;
}