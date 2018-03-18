#pragma once

#include <string>
#include <vector>

class MusicSheet {
public:
	MusicSheet(const std::string& path, const float pHeight, const int pImageWidth, const std::string& lyricsPath = "");
private:
	void makeLyrics(const std::string& lyricsPath);

	void makeSheetLines();
	void makeEighthLine(const int time);
	void makeMeasureLine(const int time);
	float height;
	int imageWidth;

	void makeNote(const int time, const int heightIndex);
	void makeXNote(const int start, const int end, const float y);
	void makeNoteCenter(const int start, const int end, const float y);
	void makeNoteLineTop(const int start, const int end, const float y);
	void makeNoteLineBottom(const int start, const int end, const float y);

	void makeLinePoints(const std::vector<float>& lines, const int start, const int end, const float xOffset, const float y);

	void resetFlags();
	bool crashNote;
	bool eighth;
	bool flipNote;
	bool flat;
	bool neutral;
	float previousHeight;

	static const float left;
	static const float right;
	static const int start;
	static const int end;
	static const int timeOffset;
	static const float timeStep;
	static const float lineSpace;
	static const float lineHeight;
	static const float noteRotation;
	static const float xRotation;
	static const float modifierOffset;
};
