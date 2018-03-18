#pragma once

#include <string>
#include <vector>

class MusicSheet {
public:
	MusicSheet(const std::string& path, const float pHeight, const int pImageWidth, const std::string& lyricsPath = "");
private:
	void makeLyrics();

	void makeSheetLines();
	void makeEighthLine(int time);
	void makeMeasureLine(int time);
	float height;
	int imageWidth;

	void makeNote(int time, int heightIndex);
	void makeXNote(int start, int end, float y);
	void makeNoteCenter(int start, int end, float y);
	void makeNoteLineTop(int start, int end, float y);
	void makeNoteLineBottom(int start, int end, float y);

	void makeLinePoints(const std::vector<float>& lines, int start, int end, float y);

	void resetFlags();
	bool crashNote = false;
	bool flipNote = false;
	bool flat = false;
	bool neutral = false;
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
