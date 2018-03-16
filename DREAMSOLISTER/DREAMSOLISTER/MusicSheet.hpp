#pragma once

#include <string>

class MusicSheet {
public:
	MusicSheet(const std::string& path, const float pHeight, const int pImageWidth);
private:
	void makeSheetLines();
	void makeEighthLine(int time);
	void makeMeasureLine(int time);
	float height;
	int imageWidth;

	void makeNote(int time, int heightIndex);
	void makeXNote(int time, float y, int trackStart);
	void makeNoteCenter(int time, float y, int trackStart);
	void makeNoteLineTop(int time, float y, int trackStart);
	void makeNoteLineBottom(int time, float y, int trackStart);
	void makeFlat(int time, int heightIndex);
	void makeNeutral(int time, int heightIndex);

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
};
