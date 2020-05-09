#pragma once

#include "S2RYBRUH/Vector2.hpp"
#include "ShapeType.hpp"

struct Shape {
	Shape() {}
	Shape(ShapeType pType, const Vector2& pPosition, const float pRotation, const Vector2& pScaleVector, const Color pColor, const int pTimeOffset)
		: type{ pType }, position{ pPosition }, rotation{ pRotation }, scaleVector{ pScaleVector }, color{ pColor }, timeOffset{ pTimeOffset } {}
	Color color;
	ShapeType type;
	Vector2 position;
	float rotation;
	Vector2 scaleVector;
	int timeOffset; // Used for ShapeVideo to determine what time a shape/transition appears at
};