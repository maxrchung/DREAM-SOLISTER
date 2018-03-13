#include "MusicSheet.hpp"
#include "OsuukiSB/Sprite.hpp"
#include <fstream>
#include <sstream>

const float MusicSheet::left = -300.0f;
const float MusicSheet::right = 300.0f;
const int MusicSheet::start = 231103;
const int MusicSheet::end = 259307;
const int MusicSheet::timeOffset = timeStep * 8;
const float MusicSheet::timeStep = 180.0f;
const float MusicSheet::lineSpace = 20.0f;
const float MusicSheet::lineHeight = 2.5f;
const float MusicSheet::noteRotation = -25 * 3.14159f / 180;

MusicSheet::MusicSheet(const std::string& path, float pHeight, int pImageWidth)
	: height{ pHeight }, imageWidth{ pImageWidth } {
	// Lines
	for (auto i = -2; i <= 2; ++i) {
		const auto y = height + i * lineSpace;
		auto const sprite = new Sprite("pixel", Vector2(left, y), Layer::Foreground, Origin::CentreLeft);
		auto const scale = Vector2(right - left, lineHeight);
		sprite->ScaleVector(start, end, scale, scale);
		sprite->Color(start, start, Color(0), Color(0));
	}

	auto fileStream = std::ifstream(path);
	if (fileStream.is_open()) {
		auto line = std::string();
		auto time = start;
		while (std::getline(fileStream, line)) {
			auto stringStream = std::stringstream(line);
			auto token = std::string();
			while (stringStream >> token) {
				if (token == "r") {
					time += timeStep;
				}
				else {
					const auto heightIndex = std::stoi(token);
					auto const note = new Sprite("circle");
					const auto y = height + heightIndex * lineSpace * 0.5f;
					const auto trackStart = time - timeOffset;
					note->Move(trackStart, time, Vector2(right, y), Vector2(left, y));
					note->Color(trackStart, trackStart, Color(0), Color(0));

					note->Rotate(trackStart, trackStart, noteRotation, noteRotation);

					const auto lineSpaceScale = lineSpace / imageWidth * 1.3f;
					const auto scale = Vector2(lineSpaceScale, lineSpaceScale * 0.8f);
					note->ScaleVector(trackStart, trackStart, scale, scale);

					Sprite* line;
					float lineRightOffset;

					if (heightIndex < 0) {
						line = new Sprite("pixel", Vector2::Zero, Layer::Foreground, Origin::BottomCentre);
						lineRightOffset = lineSpace / 2 * 1.1f;
					}
					else {
						line = new Sprite("pixel", Vector2::Zero, Layer::Foreground, Origin::TopCentre);
						lineRightOffset = -lineSpace / 2 * 1.1f;
					}

					line->ScaleVector(trackStart, trackStart, Vector2(lineHeight, 3.5f * lineSpace), Vector2(lineHeight, 3.5f * lineSpace));
					line->Move(trackStart, time, Vector2(right + lineRightOffset, y), Vector2(left + lineRightOffset, y));
					line->Color(trackStart, trackStart, Color(0), Color(0));
					time += timeStep;
				}
			}
			const auto measureLineEnd = time - timeStep / 2;
			const auto measureLineStart = measureLineEnd - timeOffset;
			auto const sprite = new Sprite("pixel");
			sprite->Move(measureLineStart, measureLineEnd, Vector2(right, 0), Vector2(left, 0));
			// + lineHeight to account for edges
			const auto scale = Vector2(lineHeight * 1.5f, lineSpace * 4 + lineHeight);
			sprite->ScaleVector(measureLineStart, measureLineStart, scale, scale);
			sprite->Color(measureLineStart, measureLineStart, Color(0), Color(0));
		}
	}
}