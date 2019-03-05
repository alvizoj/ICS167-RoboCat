class SpeedPotionClient : public SpeedPotion
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new SpeedPotionClient()); }

protected:
	SpeedPotionClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
