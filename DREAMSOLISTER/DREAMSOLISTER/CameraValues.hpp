#pragma once
#include "S2RYBRUH/Vector2.hpp"
struct CameraValues {
	explicit CameraValues(const Vector2& pCoordinate, const float pRoll, const float pScale)
		: position{ pCoordinate.x * pScale, pCoordinate.y * pScale }, roll{ pRoll }, scale{ pScale } {}
	const float roll;
	const float scale;
	const Vector2 position;
};