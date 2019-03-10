class SpeedPotion : public GameObject
{
public:
	CLASS_IDENTIFICATION('SPOT', GameObject)

		enum ESpeedPotionReplicationState
	{
		ESRS_Pose = 1 << 0,
		ESRS_Color = 1 << 1,
		ESRS_PlayerId = 1 << 2,

		ESRS_AllState = ESRS_Pose | ESRS_Color | ESRS_PlayerId
	};

	static	GameObject*	StaticCreate() { return new SpeedPotion(); }

	virtual uint32_t	GetAllStateMask()	const override { return ESRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void		Read(InputMemoryBitStream& inInputStream) override;  // Mouse, position

	void SetPlayerId(int inPlayerId) { mPlayerId = inPlayerId; }
	int GetPlayerId() const { return mPlayerId; }

	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

protected:
	SpeedPotion();
	int mPlayerId;

};
