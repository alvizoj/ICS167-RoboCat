class SpeedPotionServer : public SpeedPotion
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new SpeedPotionServer()); }
	void HandleDying()  override;
	virtual bool		HandleCollisionWithCat(RoboCat* inCat) override;
    float               SPRespawnDelay = 10;
    float               mTimeToRespawn;
    float getSPRespawnTime() { return mTimeToRespawn;}

protected:
	SpeedPotionServer();

};
