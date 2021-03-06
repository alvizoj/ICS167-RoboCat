class Server : public Engine
{
public:

	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient( ClientProxyPtr inClientProxy );
	void HandleLostClient( ClientProxyPtr inClientProxy );

	RoboCatPtr	GetCatForPlayer( int inPlayerId );
	void	SpawnCatForPlayer( int inPlayerId );
    
    void    CreateRandomSpeedPotion(int inSPotionCount);
    void    CreateRandomPotion(int inPotionCount);

private:
	Server();

	bool	InitNetworkManager();
	void	SetupWorld();

};
