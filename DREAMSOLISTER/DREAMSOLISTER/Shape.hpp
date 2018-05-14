#pragma once

#include "OsuukiSB/Vector2.hpp"
#include "ShapeType.hpp"

struct ShapeConfiguration {
	ShapeConfiguration() {}
	ShapeConfiguration(ShapeType pType, const Vector2& pPosition, const float pRotation, const Vector2& pScaleVector)
		: type{ pType }, position{ pPosition }, rotation{ pRotation }, scaleVector{ pScaleVector } {}
	ShapeType type;
	Vector2 position;
	float rotation;
	Vector2 scaleVector;
};