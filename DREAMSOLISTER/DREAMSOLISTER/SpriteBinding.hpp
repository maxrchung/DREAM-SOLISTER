#pragma once
#include "S2VX/Sprite.hpp"
#include "S2VX/Texture.hpp"
#include "OsuukiSB/Sprite.hpp"
struct SpriteBinding {
	SpriteBinding() {}
	SpriteBinding(S2VX::Sprite* pS2VXSprite)
		: S2VXSprite{ pS2VXSprite }, sprite{ new Sprite{ S2VXSprite->getTexture().getPath()} } {}
	S2VX::Sprite* S2VXSprite;
	Sprite* sprite;
};
