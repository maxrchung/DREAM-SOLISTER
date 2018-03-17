#pragma once

#include <string>
#include <vector>

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
	void makeXNote(int trackStart, int time, float y);
	void makeNoteCenter(int trackStart, int time, float y);
	void makeNoteLineTop(int trackStart, int time, float y);
	void makeNoteLineBottom(int trackStart, int time, float y);

	void makeLinePoints(const std::vector<float>& lines, int trackStart, int time, float y);

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
