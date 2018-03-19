#include "MusicSheet.hpp"
#include "LinePoints.hpp"
#include "OsuukiSB/Sprite.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

const float MusicSheet::left = -300.0f;
const float MusicSheet::right = 300.0f;
const int MusicSheet::start = 231103;
const int MusicSheet::startSheetLines = 228947;
const int MusicSheet::end = 259307;
const int MusicSheet::endSheetLines = 259756;
const float MusicSheet::timeStep = 179.64072f;
const float MusicSheet::timeOffset = timeStep * 10.0f;
const float MusicSheet::lineSpace = 10.0f;
const float MusicSheet::lineHeight = 2.0f;
const float MusicSheet::noteRotation = -25 * 3.14159f / 180;
const float MusicSheet::xRotation = 3.14159f / 4.0f;
const float MusicSheet::modifierOffset = 15.0f;
const float MusicSheet::modifierScale = lineSpace * 1.5f;
const float MusicSheet::lyricHeight = 45.0f;
const float MusicSheet::lyricSpace = 15.0f;
const float MusicSheet::lyricScale = 5.0f;
const float MusicSheet::pointScale = 1.6f;

MusicSheet::MusicSheet(const std::string& musicSheetPath, const float pHeight, const int pImageWidth, const std::string& lyricsPath)
	: height{ pHeight }, imageWidth{ pImageWidth } {
	makeSheetLines();
	if (!lyricsPath.empty()) {
		makeLyrics(lyricsPath);
	}
	makeMusicSheet(musicSheetPath);
}

void MusicSheet::makeLyrics(const std::string& path) {
	auto fileStream = std::ifstream(path);
	if (fileStream.is_open()) {
		auto line = std::string();
		auto time = static_cast<float>(start);

		while (std::getline(fileStream, line)) {
			auto stringStream = std::stringstream(line);
			auto token = std::string();

			while (stringStream >> token) {
				if (token == "r") {
					time += timeStep;
				}
				else {
					makeLyric(token, time);
					time += timeStep;	
				}
			}
		}
	}
}

void MusicSheet::makeLyric(const std::string& lyric, const float time) {
	auto startOffsetX = -lyricSpace * ((lyric.size() - 1) / 2.0f);
	auto absoluteHeight = height + lyricHeight;

	for (auto i = 0; i < lyric.size(); ++i) {
		const auto character = std::string(1, lyric[i]);
		const auto linePoints = LinePoints(character);
		const auto offsetX = startOffsetX + lyricSpace * i;
		makeLinePoints(linePoints, time - timeOffset, time, offsetX, absoluteHeight, lyricScale);
	}
}

void MusicSheet::makeMusicSheet(const std::string& path) {
	auto fileStream = std::ifstream(path);
	if (fileStream.is_open()) {
		auto line = std::string();
		auto time = static_cast<float>(start);

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

void MusicSheet::makeLinePoints(const LinePoints& linePoints, const int startTime, const int endTime, const float offsetX, const float centerY, const float scale) {
	const auto lines = linePoints.lines;
	for (auto i = 0; i < lines.size(); i += 4) {
		makeLine(lines[i], lines[i + 1], lines[i + 2], lines[i + 3], startTime, endTime, offsetX, centerY, scale);
	}

	const auto points = linePoints.points;
	for (auto i = 0; i < points.size(); i += 2) {
		makePoint(points[i], points[i + 1], startTime, endTime, offsetX, centerY, scale);
	}
}

void MusicSheet::makeLine(const float x1, const float y1, const float x2, const float y2, const int startTime, const float endTime, const float offsetX, const float centerY, const float scale) {
	const auto startPoint = Vector2(right + offsetX, centerY) + Vector2(x1, y1) * scale;
	const auto endPoint = Vector2(right + offsetX, centerY) + Vector2(x2, y2) * scale;
	const auto startPosition = (startPoint + endPoint) / 2.0f;
	const auto endPosition = Vector2(startPosition.x - right - (-left), startPosition.y);

	const auto difference = endPoint - startPoint;
	const auto distance = difference.Magnitude();
	const auto angleBetween = Vector2(1.0f, 0.0).AngleBetween(difference);
	const auto scaleVector = Vector2(distance + lineHeight, lineHeight) / imageWidth;

	auto const sprite = new Sprite("square", startPosition);
	sprite->Move(startTime, endTime, startPosition, endPosition);
	sprite->Rotate(startTime, startTime, 0, angleBetween);
	sprite->ScaleVector(startTime, startTime, scaleVector, scaleVector);
	sprite->Color(startTime, startTime, Color(0), Color(0));
}

void MusicSheet::makePoint(const float x, const float y, const int startTime, const float endTime, const float offsetX, const float centerY, const float scale) {
	const auto startPosition = Vector2(right + offsetX, centerY) + Vector2(x, y) * scale;
	const auto endPosition = Vector2(left + offsetX, centerY) + Vector2(x, y) * scale;
	const auto pointWidth = lineHeight * pointScale / imageWidth;

	auto const sprite = new Sprite("circle", startPosition);
	sprite->Color(startTime, startTime, Color(0), Color(0));
	sprite->Move(startTime, endTime, startPosition, endPosition);
	sprite->Scale(startTime, startTime, pointWidth, pointWidth);
}

void MusicSheet::makeNote(const float time, const int heightIndex) {
	const auto y = height + heightIndex * lineSpace * 0.5f;
	const auto start = time - timeOffset;

	if (flat) {
		const auto linePoints = LinePoints("flat");
		makeLinePoints(linePoints, start, time, -modifierOffset, y, modifierScale);
		flat = false;
	}

	if (neutral) {
		const auto linePoints = LinePoints("neutral");
		makeLinePoints(linePoints, start, time, -modifierOffset, y, modifierScale);
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

void MusicSheet::makeXNote(const int startTime, const int endTime, const float y) {
	// Square root of 2
	const auto length = lineSpace * 1.414f;
	const auto scale = Vector2(length, lineHeight);

	for (auto i = 0; i < 2; ++i) {
		auto const diagonal = new Sprite("pixel");
		diagonal->Move(startTime, endTime, Vector2(right, y), Vector2(left, y));
		diagonal->Color(startTime, startTime, Color(0), Color(0));
		diagonal->ScaleVector(startTime, startTime, scale, scale);

		if (i % 2 == 0) {
			diagonal->Rotate(startTime, startTime, xRotation, xRotation);
		}
		else {
			diagonal->Rotate(startTime, startTime, -xRotation, -xRotation);
		}
	}
}

void MusicSheet::makeNoteCenter(const int startTime, const int endTime, const float y) {
	const auto lineSpaceScale = lineSpace / imageWidth * 1.3f;
	const auto scale = Vector2(lineSpaceScale, lineSpaceScale * 0.8f);

	auto const note = new Sprite("circle");
	note->Move(startTime, endTime, Vector2(right, y), Vector2(left, y));
	note->Color(startTime, startTime, Color(0), Color(0));
	note->Rotate(startTime, startTime, noteRotation, noteRotation);
	note->ScaleVector(startTime, startTime, scale, scale);
}

void MusicSheet::makeNoteLineBottom(const int startTime, const int endTime, const float y) {
	const auto stretch = Vector2(lineSpace * 2, lineHeight);
	auto const centerLine = new Sprite("pixel");
	centerLine->Move(startTime, endTime, Vector2(right, y), Vector2(left, y));
	centerLine->ScaleVector(startTime, startTime, stretch, stretch);
	centerLine->Color(startTime, startTime, Color(0), Color(0));
}

void MusicSheet::makeNoteLineTop(const int startTime, const int endTime, const float y) {
	const auto stretch = Vector2(lineSpace * 2, lineHeight);
	auto const centerLine = new Sprite("pixel");
	centerLine->Move(startTime, endTime, Vector2(right, y - 0.5f * lineSpace), Vector2(left, y - 0.5f * lineSpace));
	centerLine->ScaleVector(startTime, startTime, stretch, stretch);
	centerLine->Color(startTime, startTime, Color(0), Color(0));
}

void MusicSheet::makeSheetLines() {
	for (auto i = -2; i <= 2; ++i) {
		const auto y = height + i * lineSpace;
		auto const sprite = new Sprite("pixel", Vector2(right, y), Layer::Foreground, Origin::CentreRight);
		auto const startScale = Vector2(lineHeight, lineHeight);
		auto const endScale = Vector2(right - left, lineHeight);
		sprite->ScaleVector(startSheetLines - timeOffset, startSheetLines, startScale, endScale);
		sprite->ScaleVector(endSheetLines - timeOffset, endSheetLines, endScale, startScale);
		sprite->MoveX(endSheetLines - timeOffset, endSheetLines, right, left);
		sprite->Color(start, start, Color(0), Color(0));
	}
}

void MusicSheet::makeEighthLine(const float time) {
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

void MusicSheet::makeMeasureLine(const float time) {
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