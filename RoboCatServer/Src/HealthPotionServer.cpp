#include <RoboCatServerPCH.h>


HealthPotionServer::HealthPotionServer()
{
}

void HealthPotionServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool HealthPotionServer::HandleCollisionWithCat(RoboCat* inCat)
{
	//kill yourself!
	SetDoesWantToDie(true);

	static_cast<RoboCatServer*>(inCat)->ReplenishHealth();

	return false;
}


