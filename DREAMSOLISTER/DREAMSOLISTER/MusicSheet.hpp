#pragma once

#include "OsuukiSB/Vector2.hpp"
#include "OsuukiSB/Color.hpp"
#include "LinePoints.hpp"
#include <string>
#include <vector>

class MusicSheet {
public:
	MusicSheet(const std::string& musicSheetPath, const float pHeight, const int pImageWidth, const Color& pColor, const std::string& lyricsPath, bool swapColors);
private:
	Vector2 getSpawnPosition(const Vector2& position);
	Vector2 getDespawnPosition(const Vector2& position);

	void makeLyrics(const std::string& path);
	void makeLyric(const std::string& lyric, const float time);

	void makeSheetLines();
	void makeEighthLine(const float time);
	void makeMeasureLine(const float time);

	void makeMusicSheet(const std::string& path);

	void makeNote(const float time, const int heightIndex);
	void makeXNote(const int startTime, const int endTime, const float y);
	void makeNoteCenter(const int startTime, const int endTime, const float y);
	void makeNoteLineTop(const int startTime, const int endTime, const float y);
	void makeNoteLineBottom(const int startTime, const int endTime, const float y);

	void makeLinePoints(const LinePoints& linePoints, const int startTime, const int endTime, const float offsetX, const float centerY, const float scale);
	void makeLine(const float x1, const float y1, const float x2, const float y2, const int startTime, const float endTime, const float offsetX, const float centerY, const float scale);
	void makePoint(const float x, const float y, const int startTime, const float endTime, const float offsetX, const float centerY, const float scale);

	Color getDarkerColor(const Color& color);
	Color color;
	Color darkerColor;
	Color darkestColor;
	Color getNextLyricColor();
	Color lyricColor;
	std::vector<Color> lyricColors;
	int lyricColorIndex;
	bool swappedColor;
	Color green;
	Color darkerGreen;
	Color darkestGreen;

	void resetFlags();
	bool crashNote;
	bool eighth;
	bool flipNote;
	bool flat;
	bool neutral;
	float previousHeight;

	float height;
	int imageWidth;

	static const float left;
	static const float right;
	static const int start;
	static const int startSheetLines;
	static const int end;
	static const int endSheetLines;
	static const float timeStep;
	static const float timeOffset;
	static const float lineSpace;
	static const float lineHeight;
	static const float noteRotation;
	static const float xRotation;
	static const float modifierOffset;
	static const float modifierScale;
	static const float lyricHeight;
	static const float lyricSpace;
	static const float lyricScale;
	static const float pointScale;
	static const int spawnDegrees;
	static const float spawnDistance;
	static const float spawnTime;
	static const int lastNoteTime;
};
