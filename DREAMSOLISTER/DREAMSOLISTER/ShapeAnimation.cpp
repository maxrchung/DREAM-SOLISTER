#include "ShapeAnimation.hpp"

std::unordered_map<std::string, std::vector<ShapeConfiguration>> ShapeAnimation::cache;
const std::string& ShapeAnimation::extension = ".shan";

std::vector<ShapeConfiguration> ShapeAnimation::get(const std::string& identifier) {
	if (cache.find(identifier) != cache.end()) {
		return cache[identifier];
	}
	else {
		return loadShapeConfigurations(identifier);
	}
}

std::vector<ShapeConfiguration> ShapeAnimation::loadShapeConfigurations(const std::string& identifier) {
	const auto path = identifier + extension;
	const auto data = loadJSON(path);
	const auto JSON = nlohmann::json::parse(data);
	std::vector<ShapeConfiguration> shapeConfigurations;
	shapeConfigurations.reserve(JSON.size());
	for (const auto& shape : JSON) {
		const auto __type = shape["__type"].get<std::string>();
		ShapeType type;
		if (__type == "SAEllipse:#ShapeAnimation") {
			type = ShapeType::Ellipse;
		}
		else if (__type == "SARectangle:#ShapeAnimation") {
			type = ShapeType::Rectangle;
		}
		else if (__type == "SASemicircle:#ShapeAnimation") {
			type = ShapeType::Semicircle;
		}
		else if (__type == "SATriangle:#ShapeAnimation") {
			type = ShapeType::Triangle;
		}

		const auto _position = shape["_position"];
		const auto position = Vector2(_position["x"].get<float>(), _position["y"].get<float>());

		const auto rotation = shape["_rotation"]["radian"].get<float>();

		const auto _scaleVector = shape["_scaleVector"];
		const auto scaleVector = Vector2(_scaleVector["x"].get<float>(), _scaleVector["y"].get<float>());

		const auto shapeConfiguration = ShapeConfiguration(type, position, rotation, scaleVector);
		shapeConfigurations.push_back(shapeConfiguration);
	}
	cache[identifier] = shapeConfigurations;
	return shapeConfigurations;
}

std::string ShapeAnimation::loadJSON(const std::string& path) {
	// Hmm http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
	auto in = std::ifstream(path, std::ifstream::binary);
	std::string data;
	in.seekg(0, std::ifstream::end);
	data.resize(in.tellg());
	in.seekg(0, std::ifstream::beg);
	in.read(&data[0], data.size());
	return data;
}

