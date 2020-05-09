#pragma once

#include "json.hpp"
#include "S2RYBRUH/Sprite.hpp"
#include "Shape.hpp"
#include <string>
#include <vector>

class ShapeVideo {
public:
	ShapeVideo(const std::string& ID);
	std::vector<std::vector<Shape>> shapes;
	bool isEmpty() const;
	int delta;
private:
	static std::string loadJSON(const std::string& path);
	static const std::string& extension;
	std::vector<std::vector<Shape>> loadShapes(const std::string& ID);
};