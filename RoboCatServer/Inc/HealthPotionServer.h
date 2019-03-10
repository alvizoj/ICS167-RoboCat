class HealthPotionServer : public HealthPotion
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new HealthPotionServer()); }
	void HandleDying() override;
	virtual bool		HandleCollisionWithCat(RoboCat* inCat) override;
    void                HandleHPRespawn();

protected:
	HealthPotionServer();

};
