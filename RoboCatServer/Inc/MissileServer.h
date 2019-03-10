class MissileServer : public Missile
{
public:
    static GameObjectPtr    StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new MissileServer() ); }
    void HandleDying() override;
    
    virtual bool        HandleCollisionWithCat( RoboCat* inCat ) override;
    
    virtual void Update() override;
    
protected:
    MissileServer();
    
private:
    float mTimeToDie;
    
};
