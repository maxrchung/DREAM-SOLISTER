#pragma once
#include "CameraValues.hpp"
#include "OsuukiSB/Sprite.hpp"
#include "S2VX/SpriteMoveCommand.hpp"
class SpriteGroup {
public:
	explicit SpriteGroup() {};
	explicit SpriteGroup(const std::string& path, const int pImageWidth, const int pStart, const int pEnd, const Vector2& pCenter, const float pRotation, const float pScale, const Color pColor, const int pOffset);
	void destroy();
	std::vector<Sprite*> sprites;
	Vector2 center;
private:
	Color color;
	int end;
	int imageWidth;
	int offset;
	int start;
	int startFade;
	float lineHeight;
	float overallScale;
	float rotation;
	float scale;
	static const float circleScale;
	static const float noteRotation;
	static const std::vector<float> noteLinePoints;
	static const float noteLineScale;
	static const std::vector<float> notePoint;
	static const Vector2 notePointScale;
	void makeGridSpriteGroup(const std::vector<float>& linePoints, const std::vector<float>& points);
	void makeMusicNote();
	void scalePoint(float& value);
};
