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
	void makeGridSpriteGroup(const std::vector<float>& linePoints, const std::vector<float>& points);
	void makeMusicNote();
	void makeLine(float x1, float y1, float x2, float y2, float scaleHeight);
	void makePoint(float x, float y, float pointWidth);
	void makeNote(float x, float y, Vector2 noteScale);
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
