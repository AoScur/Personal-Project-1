#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"
#include "../DataTable/PlayerStatTable.h"

class Pickup;
class Scene;
class UiMgr;


enum class FireModes
{
	PISTOL,
	SUBMACHINE,
	SWORD,
	COUNT
};

class Player : public SpriteObj
{
protected:
	Vector2f look;
	Vector2f direction; //이동방향 , 단위 벡터
	float speed;
	float accelation;
	float deaccelation;
	Vector2f velocity;

	Scene* scene;
	UiMgr* UiMgr;

	FireModes fireMode;

	// stats
	PlayerStatTable pst;
	int level;
	float reqUireExp;
	float maxHealth;
	float health;
	float damage;
	float exp;

public:
	Player();
	virtual ~Player();
		
	virtual void Init() override;
	
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void ResetVelocity();
	void SetShootType();
	
	void OnPickupItem(Pickup* item);
	//void OnHitZombie(Zombie* zombie);

	Vector2f GetPosition();
	Vector2f GetLook();

	void SetHealth(float delta) { health += delta; }
	float GetDamage() const { return damage; }
	void SetExp(float delta) { exp += delta; }
	void SetStatData(int idx)
	{
		reqUireExp = pst.LoadReqExp(idx);
		maxHealth = pst.LoadHealth(idx);
		health = pst.LoadHealth(idx);
		damage = pst.LoadDamage(idx);
	}
	float GetReqUireExp() {	return reqUireExp; }
	float GetExp() { return exp; }
	float GetMaxHealth() { return maxHealth; }
	float GetHealth() { return health; }
};