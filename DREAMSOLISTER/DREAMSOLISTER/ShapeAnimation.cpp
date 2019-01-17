#include "ShapeAnimation.hpp"

std::unordered_map<std::string, std::vector<Shape>> ShapeAnimation::cache;
const std::string& ShapeAnimation::extension = ".shan";

ShapeAnimation::ShapeAnimation(const std::string& ID) 
	: shapes{ getShapes(ID) } {}

bool ShapeAnimation::isEmpty() const {
	return shapes.empty();
}

std::vector<Shape> ShapeAnimation::getShapes(const std::string& ID) {
	// Load if not in cache
	if (cache.find(ID) == cache.end()) {
		return loadShapes(ID);
	}
	else {
		return cache[ID];
	}
}

std::vector<Shape> ShapeAnimation::loadShapes(const std::string& ID) {
	const auto path = ID + extension;
	const auto data = loadJSON(path);

	std::vector<Shape> shapes;
	nlohmann::json JSON;
	try {
		JSON = nlohmann::json::parse(data);
	}
	// Return empty if JSON failed to parse
	catch (const std::exception& e) {
		return shapes;
	}

	shapes.reserve(JSON.size());
	for (const auto& SAShape : JSON) {
		const auto __type = SAShape["__type"].get<std::string>();
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

		const auto _position = SAShape["_position"];
		const auto position = Vector2(_position["x"].get<float>(), _position["y"].get<float>());
		// Position x and y needs to be from -1 to 1 with 0 in the center
		const auto convertedPosition = Vector2(position.x, -position.y) + Vector2(-450, 450);
		const auto normalizedPosition = convertedPosition / 900.0f;

		const auto rotation = SAShape["_rotation"]["radian"].get<float>();

		const auto _scaleVector = SAShape["_scaleVector"];
		const auto scaleVector = Vector2(_scaleVector["x"].get<float>(), _scaleVector["y"].get<float>());

		const auto _color = SAShape["_color"];
		const auto color = Color(_color["R"].get<float>(), _color["G"].get<float>(), _color["B"].get<float>());

		const auto shape = Shape(type, normalizedPosition, rotation, scaleVector, color);
		shapes.push_back(shape);
	}
	cache[ID] = shapes;
	return shapes;
}

std::string ShapeAnimation::loadJSON(const std::string& path) {
	// Hmm http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
	auto in = std::ifstream(path, std::ifstream::binary);
	std::string data;
	if (in) {
		in.seekg(0, std::ifstream::end);
		data.resize(in.tellg());
		in.seekg(0, std::ifstream::beg);
		in.read(&data[0], data.size());
	}
	return data;
}

