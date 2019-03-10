class Missile : public GameObject
{
public:
    
    CLASS_IDENTIFICATION( 'MISL', GameObject )
    
    enum EMissileReplicationState
    {
        EMRS_Pose            = 1 << 0,
        EMRS_Color            = 1 << 1,
        EMRS_PlayerId        = 1 << 2,
        
        EMRS_AllState    = EMRS_Pose | EMRS_Color | EMRS_PlayerId
    };
    
    static    GameObject*    StaticCreate() { return new Missile(); }
    
    virtual uint32_t    GetAllStateMask()    const override    { return EMRS_AllState; }
    
    virtual uint32_t    Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const override;
    
    void            SetVelocity( const Vector3& inVelocity )    { mVelocity = inVelocity; }
    const Vector3&    GetVelocity() const                    { return mVelocity; }
    
    void        SetPlayerId( int inPlayerId )    { mPlayerId = inPlayerId; }
    int            GetPlayerId() const                { return mPlayerId; }
    
    void        InitFromShooter( RoboCat* inShooter );
    
    virtual void Update() override;
    
    virtual bool HandleCollisionWithCat( RoboCat* inCat ) override;
    
protected:
    Missile();
    
    
    Vector3        mVelocity;
    
    float        mMuzzleSpeed;
    int            mPlayerId;
    
};

typedef shared_ptr< Missile >    MissilePtr;
