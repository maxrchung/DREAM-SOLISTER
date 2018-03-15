#include "MusicSheet.hpp"
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

MusicSheet::MusicSheet(const std::string& path, const float pHeight, const int pImageWidth)
	: height{ pHeight }, imageWidth{ pImageWidth } {
	// Lines
	for (auto i = -2; i <= 2; ++i) {
		const auto y = height + i * lineSpace;
		auto const sprite = new Sprite("pixel", Vector2(left, y), Layer::Foreground, Origin::CentreLeft);
		auto const scale = Vector2(right - left, lineHeight);
		sprite->ScaleVector(start - timeOffset, end, scale, scale);
		sprite->Color(start, start, Color(0), Color(0));
	}

	auto fileStream = std::ifstream(path);
	if (fileStream.is_open()) {
		auto line = std::string();
		auto time = start;
		auto crashNote = false;
		auto flipNote = false;
		float previousHeight;

		while (std::getline(fileStream, line)) {
			auto stringStream = std::stringstream(line);
			auto token = std::string();

			while (stringStream >> token) {
				if (token == "r") {
					time += timeStep;
				}
				else if (token == "flipNote") {
					flipNote = true;
				}
				else if (token == "quarterSubtract") {
					time -= timeStep;
				}
				else if (token == "eighthSubtract") {
					time -= timeStep / 2;
				}
				// lol
				else if (token == "crash") {
					crashNote = true;
				}
				// Hardcode
				else if (token == "eighthLine") {
					const auto previousTime = time - timeStep;
					const auto previousLineOffset = -lineSpace / 2 - lineHeight / 2;
					const auto noteHeight = height - 3.0f * lineSpace;
					const auto trackStart = previousTime - timeOffset;
					const auto distance = (timeStep / 2) / timeOffset * (right - left);
					const auto scale = Vector2(distance + lineHeight, lineHeight);
					 
					const auto line = new Sprite("pixel", Vector2::Zero, Layer::Foreground, Origin::CentreLeft);
					line->Move(trackStart, previousTime, Vector2(right + previousLineOffset, noteHeight), Vector2(left + previousLineOffset, noteHeight));
					line->ScaleVector(trackStart, trackStart, scale, scale);
					line->Color(trackStart, trackStart, Color(0), Color(0));

					time -= timeStep / 2;
				}
				else {
					const auto heightIndex = std::stoi(token);
					const auto y = height + heightIndex * lineSpace * 0.5f;
					const auto trackStart = time - timeOffset;
					auto crashNoteOffset = false;

					if (crashNote) {
						crashNoteOffset = true;
						// Square root of 2
						const auto length = lineSpace * 1.414f;
						const auto scale = Vector2(length, lineHeight);

						for (auto i = 0; i < 2; ++i) {
							auto const diagonal = new Sprite("pixel");
							diagonal->Move(trackStart, time, Vector2(right, y), Vector2(left, y));
							diagonal->Color(trackStart, trackStart, Color(0), Color(0));
							diagonal->ScaleVector(trackStart, trackStart, scale, scale);

							if (i % 2 == 0) {
								diagonal->Rotate(trackStart, trackStart, xRotation, xRotation);
							}
							else {
								diagonal->Rotate(trackStart, trackStart, -xRotation, -xRotation);
							}
						}

						crashNote = false;
					}
					else {
						const auto lineSpaceScale = lineSpace / imageWidth * 1.3f;
						const auto scale = Vector2(lineSpaceScale, lineSpaceScale * 0.8f);

						auto const note = new Sprite("circle");
						note->Move(trackStart, time, Vector2(right, y), Vector2(left, y));
						note->Color(trackStart, trackStart, Color(0), Color(0));
						note->Rotate(trackStart, trackStart, noteRotation, noteRotation);
						note->ScaleVector(trackStart, trackStart, scale, scale);
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

					if (crashNoteOffset) {
						float previousHeightOffset = y - previousHeight;
						stem->Move(trackStart, time, Vector2(right + lineRightOffset, y - 0.5f * lineSpace), Vector2(left + lineRightOffset, y - 0.5f * lineSpace));
						stem->ScaleVector(trackStart, trackStart, Vector2(lineHeight, previousHeightOffset), Vector2(lineHeight, previousHeightOffset));
					}
					else {
						stem->Move(trackStart, time, Vector2(right + lineRightOffset, y), Vector2(left + lineRightOffset, y));
						stem->ScaleVector(trackStart, trackStart, Vector2(lineHeight, 3.5f * lineSpace), Vector2(lineHeight, 3.5f * lineSpace));
					}
					stem->Color(trackStart, trackStart, Color(0), Color(0));

					// Hardcode
					if (heightIndex == -6) {
						const auto stretch = Vector2(lineSpace * 2, lineHeight);
						auto const centerLine = new Sprite("pixel");
						centerLine->Move(trackStart, time, Vector2(right, y), Vector2(left, y));
						centerLine->ScaleVector(trackStart, trackStart, stretch, stretch);
						centerLine->Color(trackStart, trackStart, Color(0), Color(0));
					}
					else if (heightIndex == 7) {
						const auto stretch = Vector2(lineSpace * 2, lineHeight);
						auto const centerLine = new Sprite("pixel");
						centerLine->Move(trackStart, time, Vector2(right, y - 0.5f * lineSpace), Vector2(left, y - 0.5f * lineSpace));
						centerLine->ScaleVector(trackStart, trackStart, stretch, stretch);
						centerLine->Color(trackStart, trackStart, Color(0), Color(0));
					}

					previousHeight = y;
					flipNote = false;
					time += timeStep;
				}
			}

			const auto measureLineEnd = time - timeStep / 2;
			const auto measureLineStart = measureLineEnd - timeOffset;
			// + lineHeight to account for edges
			const auto scale = Vector2(lineHeight * 1.5f, lineSpace * 4 + lineHeight);

			auto const sprite = new Sprite("pixel");
			sprite->Move(measureLineStart, measureLineEnd, Vector2(right, height), Vector2(left, height));
			sprite->ScaleVector(measureLineStart, measureLineStart, scale, scale);
			sprite->Color(measureLineStart, measureLineStart, Color(0), Color(0));
		}
	}
}