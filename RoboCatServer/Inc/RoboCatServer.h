enum ECatControlType
{
	ESCT_Human,
	ESCT_AI
};

class RoboCatServer : public RoboCat
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new RoboCatServer() ); }
	virtual void HandleDying() override;

	virtual void Update() override;

	void SetCatControlType( ECatControlType inCatControlType ) { mCatControlType = inCatControlType; }

	void TakeDamage( int inDamagingPlayerId );
    void TakeMissileDamage( int inDamagingPlayerId);
	void ReplenishHealth();
	void SpeedBoost();

protected:
	RoboCatServer();

private:

	void HandleShooting();
    void HandleShootingMissile();
    void HandleSPRespawn();
    
    float SPTimeToRespawn = 10;
    float HPTimeToRespawn = 10;

	ECatControlType	mCatControlType;

    float		mTimeOfNextShot;
	float		mTimeBetweenShots;
    
    bool        boosted;
    float       mTimeSpeedBoostEnds;
};
