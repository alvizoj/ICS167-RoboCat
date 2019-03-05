#include <RoboCatClientPCH.h>

SpeedPotionClient::SpeedPotionClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("speed"));
}