#pragma once
#include "SpriteGroup.hpp"
#include "S2VX/Sprite.hpp"
#include "S2VX/Texture.hpp"
#include "S2VX/SpriteMoveCommand.hpp"
#include "S2RYBRUH/Sprite.hpp"

struct SpriteBinding {
	SpriteBinding() {}
	explicit SpriteBinding(S2VX::Sprite* pS2VXSprite, const SpriteGroup& pSpriteGroup)
		: S2VXSprite{ pS2VXSprite }, spriteGroup{ pSpriteGroup } {}
	S2VX::Sprite* S2VXSprite;
	SpriteGroup spriteGroup;
};
