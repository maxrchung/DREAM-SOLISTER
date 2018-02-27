#pragma once
#include "CameraValues.hpp"
#include "OsuukiSB/Sprite.hpp"
#include "S2VX/SpriteMoveCommand.hpp"
class SpriteGroup {
public:
	explicit SpriteGroup() {};
	explicit SpriteGroup(const std::string& path, const int pImageWidth, const int pStart, const int pEnd, const Vector2& pCenter, const float pRotation, const float pScale, const int pOffset);
	void destroy();
	std::vector<Sprite*> sprites;
	Vector2 center;
private:
	int imageWidth;
	int start;
	int end;
	float lineHeight;
	int offset;
	float circleScale;
	float overallScale;
	float rotation;
	float scale;
	void makeSpriteGroup(const std::vector<float>& linePoints, const std::vector<float>& points);
	void scalePoint(float& value);
};
