#pragma once

#include "json.hpp"
#include "OsuukiSB/Sprite.hpp"
#include "ShapeConfiguration.hpp"
#include <string>
#include <vector>
#include <unordered_map>

class ShapeAnimation {
public:
	static std::vector<ShapeConfiguration> get(const std::string& identifier);
private:
	static std::vector<ShapeConfiguration> loadShapeConfigurations(const std::string& identifier);
	static std::string loadJSON(const std::string& path);
	static std::unordered_map<std::string, std::vector<ShapeConfiguration>> cache;
	static const std::string& extension;
};