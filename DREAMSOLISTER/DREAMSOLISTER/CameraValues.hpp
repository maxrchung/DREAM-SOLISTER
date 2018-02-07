#pragma once
#include "Vector3.hpp"
struct CameraValues {
	CameraValues(const Vector3& pPosition, const float pRoll, const float pScale)
		: position{ pPosition }, roll{ pRoll }, scale{ pScale } {}
	const Vector3 position;
	const float roll;
	const float scale;
};
