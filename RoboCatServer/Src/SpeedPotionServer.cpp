#include <RoboCatServerPCH.h>

SpeedPotionServer::SpeedPotionServer()
{
}

void SpeedPotionServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}


bool SpeedPotionServer::HandleCollisionWithCat(RoboCat* inCat)
{
	//kill yourself!
	SetDoesWantToDie(true);

	static_cast<RoboCatServer*>(inCat)->SpeedBoost();

	return false;
}


