#include <RoboCatServerPCH.h>


MissileServer::MissileServer()
{
    //missile lives 5 seconds...
    mTimeToDie = Timing::sInstance.GetFrameStartTime() + 5.f;
}

void MissileServer::HandleDying()
{
    NetworkManagerServer::sInstance->UnregisterGameObject( this );
}


void MissileServer::Update()
{
    Missile::Update();
    
    if( Timing::sInstance.GetFrameStartTime() > mTimeToDie )
    {
        SetDoesWantToDie( true );
    }
    
}

bool MissileServer::HandleCollisionWithCat( RoboCat* inCat )
{
    if( inCat->GetPlayerId() != GetPlayerId() )
    {
        //kill yourself!
        SetDoesWantToDie( true );
        
        static_cast< RoboCatServer* >( inCat )->TakeMissileDamage( GetPlayerId() );
        
    }
    
    return false;
}
