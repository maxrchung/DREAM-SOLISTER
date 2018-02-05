#include "Display.hpp"
#include "Scripting.hpp"
#include "Sprite.hpp"
int main() {
	S2VX::Display display;
	S2VX::Scripting scripting{ display };
	auto elements = scripting.evaluate("DREAMSOLISTER.chai");
	auto lel = new Sprite("");
	return 0;
}