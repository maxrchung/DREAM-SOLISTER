#pragma once

#include "json.hpp"
#include "OsuukiSB/Sprite.hpp"
#include "Shape.hpp"
#include <string>
#include <vector>
#include <unordered_map>

class ShapeAnimation {
public:
	ShapeAnimation(const std::string& ID);
	std::vector<Shape> shapes;
	bool isEmpty() const;
private:
	static std::vector<Shape> getShapes(const std::string& ID);
	static std::vector<Shape> loadShapes(const std::string& ID);
	static std::string loadJSON(const std::string& path);
	static std::unordered_map<std::string, std::vector<Shape>> cache;
	static const std::string& extension;
};