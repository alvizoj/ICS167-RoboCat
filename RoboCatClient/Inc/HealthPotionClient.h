class HealthPotionClient : public HealthPotion
{
public:
	static	GameObjectPtr	StaticCreate() { return GameObjectPtr(new HealthPotionClient()); }

protected:
	HealthPotionClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};
