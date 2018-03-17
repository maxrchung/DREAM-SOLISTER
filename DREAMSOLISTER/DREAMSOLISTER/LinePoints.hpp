#pragma once

#include <string>
#include <vector>

class LinePoints {
public:
	LinePoints(const std::string& path);
	bool isEmpty() const;
	std::vector<float> lines;
	std::vector<float> points;
};