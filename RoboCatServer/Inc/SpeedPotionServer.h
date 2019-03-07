class SpeedPotionServer : public SpeedPotion
{
public:
	static GameObjectPtr	StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn(new SpeedPotionServer()); }
	void HandleDying() override;
	virtual bool		HandleCollisionWithCat(RoboCat* inCat) override;

protected:
	SpeedPotionServer();


};
