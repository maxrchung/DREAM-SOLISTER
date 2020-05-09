#include "ShapeVideo.hpp"
#include <map>

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

	std::map<int, Shape> idToShapes;

	const auto frames = JSON["frames"];
	for (const auto& frame : frames) {
		for (const auto& item : frame.items()) {
			const auto id = item.key();
			const auto config = item.value();
			const auto colorR = config["colorR"].get<int>();
			const auto colorG = config["colorG"].get<int>();
			const auto colorB = config["colorB"].get<int>();
			const auto positionX = config["positionX"].get<float>();
			const auto positionY = config["positionY"].get<float>();
			const auto rotation = config["rotation"].get<float>();
			const auto scaleX = config["scaleX"].get<float>();
			const auto scaleY = config["scaleY"].get<float>();
			const auto type = config["type"].get<std::string>();
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

