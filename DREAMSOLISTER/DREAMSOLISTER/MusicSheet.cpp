#include "MusicSheet.hpp"
#include "LinePoints.hpp"
#include "OsuukiSB/Sprite.hpp"
#include <fstream>
#include <sstream>

const float MusicSheet::left = -300.0f;
const float MusicSheet::right = 300.0f;
const int MusicSheet::start = 231103;
const int MusicSheet::end = 259307;
const int MusicSheet::timeOffset = timeStep * 10;
const float MusicSheet::timeStep = 180.0f;
const float MusicSheet::lineSpace = 10.0f;
const float MusicSheet::lineHeight = 2.0f;
const float MusicSheet::noteRotation = -25 * 3.14159f / 180;
const float MusicSheet::xRotation = 3.14159f / 4.0f;
const float MusicSheet::modifierOffset = 15.0f;

MusicSheet::MusicSheet(const std::string& path, const float pHeight, const int pImageWidth, const std::string& lyricsPath)
	: height{ pHeight }, imageWidth{ pImageWidth } {
	if (!lyricsPath.empty()) {
		makeLyrics(lyricsPath);
	}

	makeSheetLines();

	auto fileStream = std::ifstream(path);
	if (fileStream.is_open()) {
		auto line = std::string();
		auto time = start;

		while (std::getline(fileStream, line)) {
			auto stringStream = std::stringstream(line);
			auto token = std::string();

			resetFlags();

			while (stringStream >> token) {
				if (token == "r") {
					time += timeStep;
				}
				else if (token == "flat") {
					flat = true;
				}
				else if (token == "neutral") {
					neutral = true;
				}
				else if (token == "flipNote") {
					flipNote = true;
				}
				else if (token == "quarterSubtract") {
					time -= timeStep;
				}
				else if (token == "eighthSubtract") {
					eighth = true;
					time -= timeStep / 2;
				}
				else if (token == "crash") {
					crashNote = true;
				}
				// Hardcode
				else if (token == "eighthLine") {
					makeEighthLine(time);
					time -= timeStep / 2;
				}
				else {
					const auto heightIndex = std::stoi(token);
					makeNote(time, heightIndex);
					time += timeStep;
				}
			}
			makeMeasureLine(time);
		}
	}
}

void MusicSheet::makeLyrics(const std::string& lyricsPath) {

}

void MusicSheet::makeLinePoints(const std::vector<float>& lines, const int start, const int end, const float xOffset, const float y) {
	for (auto i = 0; i < lines.size(); i += 4) {
		const auto startPoint = Vector2(right - modifierOffset, y) + Vector2(lines[i], lines[i + 1]) * lineSpace * 1.5f;
		const auto endPoint = Vector2(right - modifierOffset, y) + Vector2(lines[i + 2], lines[i + 3]) * lineSpace * 1.5f;
		const auto startPosition = (startPoint + endPoint) / 2.0f;
		const auto endPosition = Vector2(startPosition.x - right - (-left), startPosition.y);

		const auto difference = endPoint - startPoint;
		const auto distance = difference.Magnitude();
		const auto angleBetween = Vector2(1.0f, 0.0).AngleBetween(difference);
		const auto scale = Vector2(distance + lineHeight, lineHeight) / imageWidth;

		auto const sprite = new Sprite("square", startPosition);
		sprite->Move(start, end, startPosition, endPosition);
		sprite->Rotate(start, start, 0, angleBetween);
		sprite->ScaleVector(start, start, scale, scale);
		sprite->Color(start, start, Color(0), Color(0));
	}
}

void MusicSheet::makeNote(const int time, const int heightIndex) {
	const auto y = height + heightIndex * lineSpace * 0.5f;
	const auto start = time - timeOffset;

	if (flat) {
		const auto lines = LinePoints("flat").lines;
		makeLinePoints(lines, start, time, 0, y);
		flat = false;
	}

	if (neutral) {
		const auto lines = LinePoints("neutral").lines;
		makeLinePoints(lines, start, time, 0, y);
		neutral = false;
	}

	Sprite* stem;
	float lineRightOffset;
	bool noteIsRight = false;
	if (heightIndex < 0) {
		noteIsRight = true;
	}
	if (flipNote) {
		noteIsRight = !noteIsRight;
	}

	if (noteIsRight) {
		stem = new Sprite("pixel", Vector2::Zero, Layer::Foreground, Origin::BottomCentre);
		lineRightOffset = lineSpace / 2;
	}
	else {
		stem = new Sprite("pixel", Vector2::Zero, Layer::Foreground, Origin::TopCentre);
		lineRightOffset = -lineSpace / 2;
	}

	if (crashNote) {
		makeXNote(start, time, y);

		float previousHeightOffset = y - previousHeight;
		stem->Move(start, time, Vector2(right + lineRightOffset, y - 0.5f * lineSpace), Vector2(left + lineRightOffset, y - 0.5f * lineSpace));
		stem->ScaleVector(start, start, Vector2(lineHeight, previousHeightOffset), Vector2(lineHeight, previousHeightOffset));

		crashNote = false;
	}
	else {
		makeNoteCenter(start, time, y);
		stem->Move(start, time, Vector2(right + lineRightOffset, y), Vector2(left + lineRightOffset, y));
		stem->ScaleVector(start, start, Vector2(lineHeight, 3.5f * lineSpace), Vector2(lineHeight, 3.5f * lineSpace));
	}
	stem->Color(start, start, Color(0), Color(0));

	// Hardcode
	if (heightIndex == -6) {
		makeNoteLineBottom(start, time, y);
	}
	else if (heightIndex == 7) {
		makeNoteLineTop(start, time, y);
	}

	previousHeight = y;
	flipNote = false;
}

void MusicSheet::resetFlags() {
	crashNote = false;
	eighth = false;
	flipNote = false;
	flat = false;
	neutral = false;
	previousHeight = 0.0f;
}

void MusicSheet::makeXNote(const int start, const int end, const float y) {
	// Square root of 2
	const auto length = lineSpace * 1.414f;
	const auto scale = Vector2(length, lineHeight);

	for (auto i = 0; i < 2; ++i) {
		auto const diagonal = new Sprite("pixel");
		diagonal->Move(start, end, Vector2(right, y), Vector2(left, y));
		diagonal->Color(start, start, Color(0), Color(0));
		diagonal->ScaleVector(start, start, scale, scale);

		if (i % 2 == 0) {
			diagonal->Rotate(start, start, xRotation, xRotation);
		}
		else {
			diagonal->Rotate(start, start, -xRotation, -xRotation);
		}
	}
}

void MusicSheet::makeNoteCenter(const int start, const int end, const float y) {
	const auto lineSpaceScale = lineSpace / imageWidth * 1.3f;
	const auto scale = Vector2(lineSpaceScale, lineSpaceScale * 0.8f);

	auto const note = new Sprite("circle");
	note->Move(start, end, Vector2(right, y), Vector2(left, y));
	note->Color(start, start, Color(0), Color(0));
	note->Rotate(start, start, noteRotation, noteRotation);
	note->ScaleVector(start, start, scale, scale);
}

void MusicSheet::makeNoteLineBottom(const int start, const int end, const float y) {
	const auto stretch = Vector2(lineSpace * 2, lineHeight);
	auto const centerLine = new Sprite("pixel");
	centerLine->Move(start, end, Vector2(right, y), Vector2(left, y));
	centerLine->ScaleVector(start, start, stretch, stretch);
	centerLine->Color(start, start, Color(0), Color(0));
}

void MusicSheet::makeNoteLineTop(const int start, const int end, const float y) {
	const auto stretch = Vector2(lineSpace * 2, lineHeight);
	auto const centerLine = new Sprite("pixel");
	centerLine->Move(start, end, Vector2(right, y - 0.5f * lineSpace), Vector2(left, y - 0.5f * lineSpace));
	centerLine->ScaleVector(start, start, stretch, stretch);
	centerLine->Color(start, start, Color(0), Color(0));
}

void MusicSheet::makeSheetLines() {
	for (auto i = -2; i <= 2; ++i) {
		const auto y = height + i * lineSpace;
		auto const sprite = new Sprite("pixel", Vector2(left, y), Layer::Foreground, Origin::CentreLeft);
		auto const scale = Vector2(right - left, lineHeight);
		sprite->ScaleVector(start - timeOffset, end, scale, scale);
		sprite->Color(start, start, Color(0), Color(0));
	}
}

void MusicSheet::makeEighthLine(const int time) {
	const auto previousTime = time - timeStep;
	const auto previousLineOffset = -lineSpace / 2 - lineHeight / 2;
	const auto noteHeight = height - 3.0f * lineSpace;
	const auto start = previousTime - timeOffset;
	const auto distance = (timeStep / 2) / timeOffset * (right - left);
	const auto scale = Vector2(distance + lineHeight, lineHeight);

	const auto line = new Sprite("pixel", Vector2::Zero, Layer::Foreground, Origin::CentreLeft);
	line->Move(start, previousTime, Vector2(right + previousLineOffset, noteHeight), Vector2(left + previousLineOffset, noteHeight));
	line->ScaleVector(start, start, scale, scale);
	line->Color(start, start, Color(0), Color(0));
}

void MusicSheet::makeMeasureLine(const int time) {
	float measureLineEnd;
	if (eighth) {
		measureLineEnd = time - timeStep / 4;
	}
	else {
		measureLineEnd = time - timeStep / 2;
	}
	const auto measureLineStart = measureLineEnd - timeOffset;
	// + lineHeight to account for edges
	const auto scale = Vector2(lineHeight * 1.5f, lineSpace * 4 + lineHeight);

	auto const sprite = new Sprite("pixel");
	sprite->Move(measureLineStart, measureLineEnd, Vector2(right, height), Vector2(left, height));
	sprite->ScaleVector(measureLineStart, measureLineStart, scale, scale);
	sprite->Color(measureLineStart, measureLineStart, Color(0), Color(0));
}