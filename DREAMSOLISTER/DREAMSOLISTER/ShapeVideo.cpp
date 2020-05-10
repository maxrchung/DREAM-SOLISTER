#include "ShapeVideo.hpp"
#include <unordered_map>

const std::string& ShapeVideo::extension = ".sheo";

ShapeVideo::ShapeVideo(const std::string& ID)
	: shapes{ loadShapes(ID) } {}

bool ShapeVideo::isEmpty() const {
	return shapes.empty();
}

std::vector<std::vector<Shape>> ShapeVideo::loadShapes(const std::string& ID) {
	const auto path = ID + extension;
	const auto data = loadJSON(path);

	std::vector<std::vector<Shape>> shapes;
	nlohmann::json JSON;
	try {
		JSON = nlohmann::json::parse(data);
	}
	// Return empty if JSON failed to parse
	catch (const std::exception& e) {
		return shapes;
	}

	std::map<int, std::vector<Shape>> IDToShapes;
	const auto frames = JSON["frames"];

	std::vector<int> layers;
	const auto JSONLayers = JSON["layers"];
	layers.reserve(JSONLayers.size());
	for (auto i = 0; i < JSONLayers.size(); ++i) {
		layers.push_back(JSONLayers[i].get<int>());
	}

	auto timeOffset = 0;
	const auto delta = std::stoi(JSON["framesDelta"].get<std::string>());
	this->delta = delta;
	for (const auto& frame : frames) {
		for (const auto& item : frame.items()) {
			const auto ID = std::stoi(item.key());
			const auto config = item.value();

			const auto color = Color(config["colorR"].get<int>(), config["colorG"].get<int>(), config["colorB"].get<int>());
			const auto position = Vector2(config["positionX"].get<float>(), -config["positionY"].get<float>());
			const auto rotation = config["rotation"].get<float>();
			const auto scaleVector = Vector2(config["scaleX"].get<float>(), config["scaleY"].get<float>());
			const auto JSONType = config["type"].get<std::string>();
			ShapeType type;
			if (JSONType == "Rectangle") {
				type = ShapeType::Rectangle;
			}
			else if (JSONType == "Triangle") {
				type = ShapeType::Triangle;
			}
			else if (JSONType == "Circle") {
				type = ShapeType::Ellipse;
			}
			else if (JSONType == "Semicircle") {
				type = ShapeType::Semicircle;
			}

			const auto shape = Shape(type, position, rotation, scaleVector, color, timeOffset);
			if (IDToShapes.find(ID) == IDToShapes.end()) {
				IDToShapes[ID] = { shape };
			}
			else {
				IDToShapes[ID].push_back(shape);
			}
		}
		timeOffset += delta;
	}

	for (const auto layer : layers) {
		if (IDToShapes.find(layer) != IDToShapes.end()) {
			shapes.push_back(IDToShapes[layer]);
		}
	}

	return shapes;
}

std::string ShapeVideo::loadJSON(const std::string& path) {
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

