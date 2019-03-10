class MissileClient : public Missile
{
public:
    static GameObjectPtr  StaticCreate()        { return GameObjectPtr( new MissileClient); }
    
    virtual void        Read( InputMemoryBitStream& inInputStream ) override;
    
protected:
    MissileClient();
    
private:
    
    SpriteComponentPtr    mSpriteComponent;
};
