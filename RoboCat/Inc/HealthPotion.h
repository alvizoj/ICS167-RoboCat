class HealthPotion : public GameObject
{
public:
	CLASS_IDENTIFICATION('HPOT', GameObject)

		enum EHealthPotionReplicationState
	{
		EHRS_Pose = 1 << 0,
		EHRS_Color = 1 << 1,
		EHRS_PlayerId = 1 << 2,

		EHRS_AllState = EHRS_Pose | EHRS_Color | EHRS_PlayerId
	};

	static	GameObject*	StaticCreate() { return new HealthPotion(); }

	virtual uint32_t	GetAllStateMask()	const override { return EHRS_AllState; }

	virtual uint32_t	Write(OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState) const override;
	virtual void		Read(InputMemoryBitStream& inInputStream) override;  // Mouse, position

	void SetPlayerId(int inPlayerId) { mPlayerId = inPlayerId; }
	int GetPlayerId() const { return mPlayerId; }

	virtual bool HandleCollisionWithCat(RoboCat* inCat) override;

protected:
	HealthPotion();
	int mPlayerId;

};
