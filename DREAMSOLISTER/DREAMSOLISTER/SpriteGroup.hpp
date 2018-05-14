#pragma once
#include "CameraValues.hpp"
#include "LinePoints.hpp"
#include "OsuukiSB/Sprite.hpp"
#include "ShapeAnimation.hpp"
#include "S2VX/SpriteMoveCommand.hpp"
class SpriteGroup {
public:
	explicit SpriteGroup() {};
	explicit SpriteGroup(const std::string& ID, const int pImageWidth, const int pStart, const int pEnd, const Vector2& pCenter, const float pRotation, const float pScale, const Color pColor, const int pOffset);
	void destroy();
	std::vector<Sprite*> sprites;
	Vector2 center;
private:
	void makeShapes(const ShapeAnimation& shapes);
	void makeLinePoints(const LinePoints& linePoints);
	void makeMusicNote();
	void makeLine(const float x1, const float y1, const float x2, const float y2, const float scaleHeight);
	void makePoint(const float x, const float y, const float pointWidth);
	void makeNote(const float x, const float y, const const Vector2& noteScale);
	void scalePoint(float& value);
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

};
