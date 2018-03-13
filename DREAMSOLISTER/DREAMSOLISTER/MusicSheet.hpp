#pragma once

#include <string>

class MusicSheet {
public:
	MusicSheet(const std::string& path, float pHeight, int pImageWidth);
private:
	float height;
	int imageWidth;
	static const float left;
	static const float right;
	static const int start;
	static const int end;
	static const int timeOffset;
	static const float timeStep;
	static const float lineSpace;
	static const float lineHeight;
	static const float noteRotation;
};
