#include "MusicSheet.hpp"
#include "LinePoints.hpp"
#include "OsuukiSB/Sprite.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>

const float MusicSheet::left = -250.0f;
const float MusicSheet::right = 350.0f;
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
const int MusicSheet::spawnDegrees = 60;
const float MusicSheet::spawnDistance = lineSpace * 3;
const float MusicSheet::spawnTime = timeStep * 2;
const int MusicSheet::lastNoteTime = 259307;
const int MusicSheet::swapTime = timeStep * 3;
const int MusicSheet::swapEndTime = 242241;
const Color MusicSheet::green = Color(119, 255, 169);
const Color MusicSheet::darkerGreen = Color(119 - 30, 255 - 30, 169 - 30);
const Color MusicSheet::darkestGreen = Color(119 - 60, 255 - 60, 169 - 60);

MusicSheet::MusicSheet(const std::string& musicSheetPath, const float pHeight, const int pImageWidth, const Color& pColor, const std::string& lyricsPath, bool pSwapColor)
	: height{ pHeight },
	imageWidth{ pImageWidth },
	color{ pColor },
	darkerColor{ getDarkerColor(color) },
	darkestColor{ getDarkerColor(darkerColor) },
	lyricColors { color, darkerColor, darkestColor, darkerColor },
	swapColor{ pSwapColor },
	swappedColor{ false } {
	makeSheetLines();
	if (!lyricsPath.empty()) {
		makeLyrics(lyricsPath);
	}
	makeMusicSheet(musicSheetPath);
}

void MusicSheet::colorSprite(Sprite* const sprite, const int startTime, const int endTime, const Color& color, const Color& greenColor) {
	if (swapColor) {
		if (startTime > swapEndTime - swapTime - timeOffset && startTime < swapEndTime - swapTime) {
			sprite->Color(swapEndTime - swapTime, swapEndTime, color, greenColor, Easing::EasingIn);
		}
		else if (endTime < swapEndTime - swapTime) {
			sprite->Color(endTime, endTime, color, color);
		}
		else if (endTime > swapEndTime) {
			sprite->Color(endTime, endTime, greenColor, greenColor);
		}
	}
	else {
		sprite->Color(endTime, endTime, color, color);
	}
}

Color MusicSheet::getDarkerColor(const Color& color) {
	auto darker = color - Color(30);
	if (darker.r < 0) {
		darker.r = 0;
	}
	if (darker.g < 0) {
		darker.g = 0;
	}
	if (darker.b < 0) {
		darker.b = 0;
	}
	return darker;
}

Color MusicSheet::getNextLyricColor() {
	return lyricColors[lyricColorIndex++ % lyricColors.size()];
}


Vector2 MusicSheet::getSpawnPosition(const Vector2& position) {
	const auto direction = rand() % spawnDegrees - spawnDegrees / 2;
	const auto radians = direction * 3.1416f / 180.0f;
	const auto spawnPosition = position + Vector2(spawnDistance, 0.0f).Rotate(radians);
	return spawnPosition;
}

Vector2 MusicSheet::getDespawnPosition(const Vector2& position) {
	const auto direction = 180 + (rand() % spawnDegrees - spawnDegrees / 2);
	const auto radians = direction * 3.1416f / 180.0f;
	const auto despawnPosition = position + Vector2(spawnDistance, 0.0f).Rotate(radians);
	return despawnPosition;
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

	lyricColor = getNextLyricColor();

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
			if (time < lastNoteTime) {
				makeMeasureLine(time);
			}
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
	const auto spawnPosition = getSpawnPosition(startPosition);
	const auto endPosition = Vector2(startPosition.x - right - (-left), startPosition.y);
	const auto despawnPosition = getDespawnPosition(endPosition);

	const auto difference = endPoint - startPoint;
	const auto distance = difference.Magnitude();
	const auto angleBetween = Vector2(1.0f, 0.0).AngleBetween(difference);
	const auto scaleVector = Vector2(distance + lineHeight, lineHeight) / imageWidth;
	const auto minScaleVector = Vector2(lineHeight, lineHeight) / imageWidth;

	auto const sprite = new Sprite("square", startPosition);
	sprite->Fade(startTime - spawnTime, startTime, 0, 1, Easing::EasingIn);
	sprite->Fade(endTime, endTime + spawnTime, 1, 0, Easing::EasingOut);

	sprite->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
	sprite->Move(startTime, endTime, startPosition, endPosition);
	sprite->Move(endTime, endTime + spawnTime, endPosition, despawnPosition, Easing::EasingOut);

	sprite->Rotate(startTime - spawnTime, startTime, 0, angleBetween, Easing::EasingIn);
	sprite->Rotate(endTime, endTime + spawnTime, angleBetween, 0, Easing::EasingOut);

	sprite->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector);
	sprite->ScaleVector(endTime, endTime + spawnTime, scaleVector, minScaleVector);

	sprite->Color(startTime, startTime, lyricColor, lyricColor);
}

void MusicSheet::makePoint(const float x, const float y, const int startTime, const float endTime, const float offsetX, const float centerY, const float scale) {
	const auto startPosition = Vector2(right + offsetX, centerY) + Vector2(x, y) * scale;
	const auto spawnPosition = getSpawnPosition(startPosition);
	const auto endPosition = Vector2(left + offsetX, centerY) + Vector2(x, y) * scale;
	const auto despawnPosition = getDespawnPosition(endPosition);
	const auto pointWidth = lineHeight * pointScale / imageWidth;

	auto const sprite = new Sprite("circle", startPosition);
	sprite->Fade(startTime - spawnTime, startTime, 0, 1, Easing::EasingIn);
	sprite->Fade(endTime, endTime + spawnTime, 1, 0, Easing::EasingOut);

	sprite->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
	sprite->Move(startTime, endTime, startPosition, endPosition);
	sprite->Move(endTime, endTime + spawnTime, endPosition, despawnPosition, Easing::EasingOut);

	sprite->Scale(startTime, startTime, pointWidth, pointWidth);
	sprite->Color(startTime, startTime, lyricColor, lyricColor);
}

void MusicSheet::makeNote(const float time, const int heightIndex) {
	const auto y = height + heightIndex * lineSpace * 0.5f;
	const auto startTime = time - timeOffset;

	if (flat) {
		const auto linePoints = LinePoints("flat");
		makeLinePoints(linePoints, startTime, time, -modifierOffset, y, modifierScale);
		flat = false;
	}

	if (neutral) {
		const auto linePoints = LinePoints("neutral");
		makeLinePoints(linePoints, startTime, time, -modifierOffset, y, modifierScale);
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
		makeXNote(startTime, time, y);

		const auto startPosition = Vector2(right + lineRightOffset, y - 0.5f * lineSpace);
		const auto spawnPosition = getSpawnPosition(startPosition);
		const auto endPosition = Vector2(left + lineRightOffset, y - 0.5f * lineSpace);
		const auto despawnPosition = getDespawnPosition(endPosition);

		const auto previousHeightOffset = y - previousHeight;
		const auto scaleVector = Vector2(lineHeight, previousHeightOffset);
		const auto minScaleVector = Vector2(lineHeight, lineHeight);


		stem->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
		stem->Move(startTime, time, startPosition, endPosition);
		stem->Move(time, time + spawnTime, endPosition, despawnPosition, Easing::EasingOut);

		stem->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector, Easing::EasingIn);
		stem->ScaleVector(time, time + spawnTime, scaleVector, minScaleVector, Easing::EasingOut);

		crashNote = false;
	}
	else {
		makeNoteCenter(startTime, time, y);

		const auto startPosition = Vector2(right + lineRightOffset, y);
		const auto spawnPosition = getSpawnPosition(startPosition);
		const auto endPosition = Vector2(left + lineRightOffset, y);
		const auto despawnPosition = getDespawnPosition(endPosition);

		const auto scaleVector = Vector2(lineHeight, 3.5f * lineSpace);
		const auto minScaleVector = Vector2(lineHeight, lineHeight);

		stem->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
		stem->Move(startTime, time, startPosition, endPosition);
		stem->Move(time, time + spawnTime, endPosition, despawnPosition, Easing::EasingOut);

		stem->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector, Easing::EasingIn);
		stem->ScaleVector(time, time + spawnTime, scaleVector, minScaleVector, Easing::EasingOut);
	}
	stem->Rotate(startTime - spawnTime, startTime, 90 * 3.14159f / 180.0f, 0, Easing::EasingIn);
	stem->Rotate(time, time + spawnTime, 0, 90 * 3.14159f / 180.0f, Easing::EasingOut);

	stem->Fade(startTime - spawnTime, startTime, 0, 1, Easing::EasingIn);
	stem->Fade(time, time + spawnTime, 1, 0, Easing::EasingOut);
	colorSprite(stem, startTime, time, darkestColor, darkestGreen);

	// Hardcode
	if (heightIndex == -6) {
		makeNoteLineBottom(startTime, time, y);
	}
	else if (heightIndex == 7) {
		makeNoteLineTop(startTime, time, y);
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
	const auto scaleVector = Vector2(length, lineHeight);
	const auto minScaleVector = Vector2(lineHeight, lineHeight);

	for (auto i = 0; i < 2; ++i) {
		const auto startPosition = Vector2(right, y);
		const auto spawnPosition = getSpawnPosition(startPosition);
		const auto endPosition = Vector2(left, y);
		const auto despawnPosition = getDespawnPosition(endPosition);

		auto const diagonal = new Sprite("pixel");
		diagonal->Fade(startTime - spawnTime, startTime, 0, 1, Easing::EasingIn);
		diagonal->Fade(endTime, endTime + spawnTime, 1, 0, Easing::EasingOut);

		diagonal->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
		diagonal->Move(startTime, endTime, startPosition, endPosition);
		diagonal->Move(endTime, endTime + spawnTime, endPosition, despawnPosition, Easing::EasingOut);
		colorSprite(diagonal, startTime, endTime, darkestColor, darkestGreen);

		diagonal->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector, Easing::EasingIn);
		diagonal->ScaleVector(endTime, endTime + spawnTime, scaleVector, minScaleVector, Easing::EasingOut);

		if (i % 2 == 0) {
			diagonal->Rotate(startTime - spawnTime, startTime, 0, xRotation, Easing::EasingIn);
			diagonal->Rotate(endTime, endTime + spawnTime, xRotation, 0, Easing::EasingOut);
		}
		else {
			diagonal->Rotate(startTime - spawnTime, startTime, 0, -xRotation, Easing::EasingIn);
			diagonal->Rotate(endTime, endTime + spawnTime, -xRotation, 0, Easing::EasingOut);
		}
	}
}

void MusicSheet::makeNoteCenter(const int startTime, const int endTime, const float y) {
	const auto lineSpaceScale = lineSpace / imageWidth * 1.3f;
	const auto scaleVector = Vector2(lineSpaceScale, lineSpaceScale * 0.8f);
	const auto minScaleVector = Vector2(lineSpaceScale * 0.8f, lineSpaceScale * 0.8f);
	const auto startPosition = Vector2(right, y);
	const auto spawnPosition = getSpawnPosition(startPosition);
	const auto endPosition = Vector2(left, y);
	const auto despawnPosition = getDespawnPosition(endPosition);

	auto const note = new Sprite("circle");
	note->Fade(startTime - spawnTime, startTime, 0, 1, Easing::EasingIn);
	note->Fade(endTime, endTime + spawnTime, 1, 0, Easing::EasingOut);

	note->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
	note->Move(startTime, endTime, startPosition, endPosition);
	note->Move(endTime, endTime + spawnTime, endPosition, despawnPosition, Easing::EasingOut);

	note->Rotate(startTime - spawnTime, startTime, 0, noteRotation, Easing::EasingIn);
	note->Rotate(endTime, endTime + spawnTime, noteRotation, 0, Easing::EasingOut);

	note->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector, Easing::EasingIn);
	note->ScaleVector(endTime, endTime + spawnTime, scaleVector, minScaleVector, Easing::EasingOut);

	colorSprite(note, startTime, endTime, darkestColor, darkestGreen);
}

void MusicSheet::makeNoteLineBottom(const int startTime, const int endTime, const float y) {
	const auto startPosition = Vector2(right, y);
	const auto spawnPosition = getSpawnPosition(startPosition);
	const auto endPosition = Vector2(left, y);
	const auto despawnPosition = getDespawnPosition(endPosition);

	const auto scaleVector = Vector2(lineSpace * 2, lineHeight);
	const auto minScaleVector = Vector2(lineHeight, lineHeight);

	auto const centerLine = new Sprite("pixel");
	centerLine->Fade(startTime - spawnTime, startTime, 0,1, Easing::EasingIn);
	centerLine->Fade(endTime, endTime + spawnTime, 1, 0, Easing::EasingOut);

	centerLine->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
	centerLine->Move(startTime, endTime, startPosition, endPosition);
	centerLine->Move(endTime, endTime + spawnTime, endPosition, despawnPosition, Easing::EasingIn);

	centerLine->Rotate(startTime - spawnTime, startTime, 90 * 3.14159f / 180.0f, 0, Easing::EasingIn);
	centerLine->Rotate(endTime, endTime + spawnTime, 0, 90 * 3.14159f / 180.0f, Easing::EasingOut);

	centerLine->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector, Easing::EasingIn);
	centerLine->ScaleVector(endTime, endTime + spawnTime, scaleVector, minScaleVector, Easing::EasingOut);

	colorSprite(centerLine, startTime, endTime, darkestColor, darkestGreen);
}

void MusicSheet::makeNoteLineTop(const int startTime, const int endTime, const float y) {
	const auto startPosition = Vector2(right, y - 0.5f * lineSpace);
	const auto spawnPosition = getSpawnPosition(startPosition);
	const auto endPosition = Vector2(left, y - 0.5f * lineSpace);
	const auto despawnPosition = getDespawnPosition(endPosition);

	const auto scaleVector = Vector2(lineSpace * 2, lineHeight);
	const auto minScaleVector = Vector2(lineHeight, lineHeight);

	auto const centerLine = new Sprite("pixel");
	centerLine->Fade(startTime - spawnTime, startTime, 0, 1, Easing::EasingIn);
	centerLine->Fade(endTime, endTime + spawnTime, 1, 0, Easing::EasingOut);

	centerLine->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
	centerLine->Move(startTime, endTime, startPosition, endPosition);
	centerLine->Move(endTime, endTime + spawnTime, endPosition, despawnPosition, Easing::EasingIn);

	centerLine->Rotate(startTime - spawnTime, startTime, 90 * 3.14159f / 180.0f, 0, Easing::EasingIn);
	centerLine->Rotate(endTime, endTime + spawnTime, 0, 90 * 3.14159f / 180.0f, Easing::EasingOut);

	centerLine->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector, Easing::EasingIn);
	centerLine->ScaleVector(endTime, endTime + spawnTime, scaleVector, minScaleVector, Easing::EasingOut);

	colorSprite(centerLine, startTime, endTime, darkestColor, darkestGreen);
}

void MusicSheet::makeSheetLines() {
	for (auto i = -2; i <= 2; ++i) {
		const auto y = height + i * lineSpace;
		auto const sprite = new Sprite("pixel", Vector2(right, y), Layer::Foreground, Origin::CentreRight);
		auto const startScale = Vector2(lineHeight, lineHeight);
		auto const endScale = Vector2(right - left, lineHeight);

		sprite->Fade(startSheetLines - timeOffset, startSheetLines, 0, 1, Easing::EasingIn);
		sprite->Fade(lastNoteTime, endSheetLines, 1, 0, Easing::EasingOut);

		sprite->ScaleVector(startSheetLines - timeOffset, startSheetLines, startScale, endScale);
		sprite->ScaleVector(endSheetLines - timeOffset, endSheetLines, endScale, startScale);
		sprite->MoveX(endSheetLines - timeOffset, endSheetLines, right, left);

		if (swapColor) {
			sprite->Color(swapEndTime - swapTime, swapEndTime, color, green, Easing::EasingIn);
		}
		else {
			sprite->Color(start, start, color, color);
		}
	}
}

void MusicSheet::makeEighthLine(const float time) {
	const auto endTime = time - timeStep;
	const auto previousLineOffset = -lineSpace / 2 - lineHeight / 2;
	const auto noteHeight = height - 3.0f * lineSpace;
	const auto startTime = endTime - timeOffset;
	const auto distance = (timeStep / 2) / timeOffset * (right - left);
	const auto scaleVector = Vector2(distance + lineHeight, lineHeight);
	const auto minScaleVector = Vector2(lineHeight, lineHeight);
	const auto startPosition = Vector2(right + previousLineOffset, noteHeight);
	const auto spawnPosition = getSpawnPosition(startPosition);
	const auto endPosition = Vector2(left + previousLineOffset, noteHeight);
	const auto despawnPosition = getDespawnPosition(endPosition);

	const auto line = new Sprite("pixel", Vector2::Zero, Layer::Foreground, Origin::CentreLeft);
	line->Fade(startTime - spawnTime, startTime, 0, 1, Easing::EasingIn);
	line->Fade(endTime, endTime + spawnTime, 1, 0, Easing::EasingOut);

	line->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
	line->Move(startTime, endTime, startPosition, endPosition);
	line->Move(endTime, endTime + spawnTime, endPosition, despawnPosition, Easing::EasingOut);

	line->Rotate(startTime - spawnTime, startTime, 90 * 3.14159f / 180.0f, 0, Easing::EasingIn);
	line->Rotate(endTime, endTime + spawnTime, 0, 90 * 3.14159f / 180.0f, Easing::EasingOut);

	line->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector, Easing::EasingIn);
	line->ScaleVector(endTime, endTime + spawnTime, scaleVector, minScaleVector, Easing::EasingOut);

	colorSprite(line, startTime, endTime, darkestColor, darkestGreen);
}

void MusicSheet::makeMeasureLine(const float time) {
	float endTime;
	if (eighth) {
		endTime = time - timeStep / 4;
	}
	else {
		endTime = time - timeStep / 2;
	}
	const auto startTime = endTime - timeOffset;
	// + lineHeight to account for edges
	const auto scaleVector = Vector2(lineHeight * 1.5f, lineSpace * 4 + lineHeight);
	const auto minScaleVector = Vector2(lineHeight * 1.5f, lineHeight * 1.5f);

	const auto startPosition = Vector2(right, height);
	const auto spawnPosition = getSpawnPosition(startPosition);
	const auto endPosition = Vector2(left, height);
	const auto despawnPosition = getDespawnPosition(endPosition);

	auto const sprite = new Sprite("pixel");
	sprite->Fade(startTime - spawnTime, startTime, 0, 1, Easing::EasingIn);
	sprite->Fade(endTime, endTime + spawnTime, 1, 0, Easing::EasingOut);

	sprite->Move(startTime - spawnTime, startTime, spawnPosition, startPosition, Easing::EasingIn);
	sprite->Move(startTime, endTime, startPosition, endPosition);
	sprite->Move(endTime, endTime + spawnTime, endPosition, despawnPosition, Easing::EasingOut);

	sprite->Rotate(startTime - spawnTime, startTime, 90 * 3.14159f / 180.0f, 0, Easing::EasingIn);
	sprite->Rotate(time, time + spawnTime, 0, 90 * 3.14159f / 180.0f, Easing::EasingOut);

	sprite->ScaleVector(startTime - spawnTime, startTime, minScaleVector, scaleVector, Easing::EasingIn);
	sprite->ScaleVector(endTime, endTime + spawnTime, scaleVector, minScaleVector, Easing::EasingOut);

	if (swapColor) {
		sprite->Color(swapEndTime - swapTime, swapEndTime, darkerColor, darkerGreen);
	}
	else {
		sprite->Color(start, start, darkerColor, darkerColor);
	}
}