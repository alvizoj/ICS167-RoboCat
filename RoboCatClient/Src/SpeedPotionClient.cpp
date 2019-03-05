#include <RoboCatClientPCH.h>

HealthPotionClient::HealthPotionClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("speed"));
}