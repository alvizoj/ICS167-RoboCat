#include <RoboCatPCH.h>

Missile::Missile() :
mMuzzleSpeed( 5.f ),
mVelocity( Vector3::Zero ),
mPlayerId( 0 )
{
    SetScale( GetScale() * 0.75f );
    SetCollisionRadius( 0.5f );
}



uint32_t Missile::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const
{
    uint32_t writtenState = 0;

    if( inDirtyState & EMRS_Pose )
    {
        inOutputStream.Write( (bool)true );

        Vector3 location = GetLocation();
        inOutputStream.Write( location.mX );
        inOutputStream.Write( location.mY );

        Vector3 velocity = GetVelocity();
        inOutputStream.Write( velocity.mX );
        inOutputStream.Write( velocity.mY );

        inOutputStream.Write( GetRotation() );

        writtenState |= EMRS_Pose;
    }
    else
    {
        inOutputStream.Write( (bool)false );
    }

    if( inDirtyState & EMRS_Color )
    {
        inOutputStream.Write( (bool)true );

        inOutputStream.Write( GetColor() );

        writtenState |= EMRS_Color;
    }
    else
    {
        inOutputStream.Write( (bool)false );
    }

    if( inDirtyState & EMRS_PlayerId )
    {
        inOutputStream.Write( (bool)true );

        inOutputStream.Write( mPlayerId, 8 );

        writtenState |= EMRS_PlayerId;
    }
    else
    {
        inOutputStream.Write( (bool)false );
    }




    return writtenState;
}



bool Missile::HandleCollisionWithCat( RoboCat* inCat )
{
    ( void ) inCat;

    //you hit a cat, so look like you hit a cat



    return false;
}


void Missile::InitFromShooter( RoboCat* inShooter )
{
    SetColor( inShooter->GetColor() );
    SetPlayerId( inShooter->GetPlayerId() );

    Vector3 forward = inShooter->GetForwardVector();
    SetVelocity( inShooter->GetVelocity() + forward * mMuzzleSpeed );
    SetLocation( inShooter->GetLocation() /* + forward * 0.55f */ );

    SetRotation( inShooter->GetRotation() );
}

void Missile::Update()
{

    float deltaTime = Timing::sInstance.GetDeltaTime();

    SetLocation( GetLocation() + mVelocity * deltaTime );


    //we'll let the cats handle the collisions
}
