#include <RoboCatServerPCH.h>

RoboCatServer::RoboCatServer() :
	mCatControlType( ESCT_Human ),
	mTimeOfNextShot( 0.f ),
	mTimeBetweenShots( 0.2f )
{}

namespace {
    const float kSpeedBoostDuration = 5.f;
}

void RoboCatServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject( this );
}

void RoboCatServer::Update()
{
	RoboCat::Update();
	
	Vector3 oldLocation = GetLocation();
	Vector3 oldVelocity = GetVelocity();
	float oldRotation = GetRotation();
    
    //if current time is > duration, reset speed
    HandleSPRespawn();
    if (boosted && Timing::sInstance.GetTimef() > mTimeSpeedBoostEnds){
        boosted = false;
        mMaxLinearSpeed /= 3;
    }
    
	ClientProxyPtr client = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
	if( client )
	{
		MoveList& moveList = client->GetUnprocessedMoveList();
		for( const Move& unprocessedMove : moveList )
		{
			const InputState& currentState = unprocessedMove.GetInputState();
			float deltaTime = unprocessedMove.GetDeltaTime();
			ProcessInput( deltaTime, currentState );
			SimulateMovement( deltaTime );
		}

		moveList.Clear();
	}

	HandleShooting();
    HandleShootingMissile();

	if( !RoboMath::Is2DVectorEqual( oldLocation, GetLocation() ) ||
		!RoboMath::Is2DVectorEqual( oldVelocity, GetVelocity() ) ||
		oldRotation != GetRotation() )
	{
		NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Pose );
	}
}

void RoboCatServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if( mIsShooting && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot )
	{
		//not exact, but okay
		mTimeOfNextShot = time + mTimeBetweenShots;

		//fire!
		YarnPtr yarn = std::static_pointer_cast< Yarn >( GameObjectRegistry::sInstance->CreateGameObject( 'YARN' ) );
		yarn->InitFromShooter( this );
	}
}

void RoboCatServer::HandleShootingMissile()
{
    float time = Timing::sInstance.GetFrameStartTime();
    if( mIsShootingMissile && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot )
    {
        //not exact, but okay
        mTimeOfNextShot = time + mTimeBetweenShots;
        
        //fire!
        MissilePtr miss = std::static_pointer_cast<
            Missile >( GameObjectRegistry::sInstance->CreateGameObject( 'MISL' ) );
        miss->InitFromShooter( this );
    }
}

void RoboCatServer::TakeDamage( int inDamagingPlayerId )
{
	mHealth--;
	if( mHealth <= 0.f )
	{
		//score one for damaging player...
		ScoreBoardManager::sInstance->IncScore( inDamagingPlayerId, 1 );

		//and you want to die
		SetDoesWantToDie( true );

		//tell the client proxy to make you a new cat
		ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
		if( clientProxy )
		{
			clientProxy->HandleCatDied();
		}
	}

	//tell the world our health dropped
	NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Health );
}

void RoboCatServer::TakeMissileDamage( int inDamagingPlayerId )
{
    mHealth -= 3;
    if( mHealth <= 0.f )
    {
        //score one for damaging player...
        ScoreBoardManager::sInstance->IncScore( inDamagingPlayerId, 1 );
        
        //and you want to die
        SetDoesWantToDie( true );
        
        //tell the client proxy to make you a new cat
        ClientProxyPtr clientProxy = NetworkManagerServer::sInstance->GetClientProxy( GetPlayerId() );
        if( clientProxy )
        {
            clientProxy->HandleCatDied();
        }
    }
    
    //tell the world our health dropped
    NetworkManagerServer::sInstance->SetStateDirty( GetNetworkId(), ECRS_Health );
}

void RoboCatServer::ReplenishHealth()
{
	mHealth = 10;
	NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Health);
}

void RoboCatServer::SpeedBoost()
{
    float current_time = Timing::sInstance.GetFrameStartTime();
    mTimeSpeedBoostEnds = current_time + kSpeedBoostDuration;
    if ((mMaxLinearSpeed < 150))
    {
        mMaxLinearSpeed *= 3;
        boosted = true;
        NetworkManagerServer::sInstance->SetStateDirty(GetNetworkId(), ECRS_Pose);
    }
	
}

void RoboCatServer::HandleSPRespawn(){
    
    if( SPTimeToRespawn != 0.f && Timing::sInstance.GetFrameStartTime() > SPTimeToRespawn )
    {
        static_cast< Server* > ( Engine::sInstance.get() )->CreateRandomSpeedPotion(1);
        SPTimeToRespawn = 0.f;
        //SpeedPotionServer::getSPRespawnTime();
    }
}
