#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"
#include "../DataTable/PlayerStatTable.h"

#include "../Framework/Animator.h"

class Pickup;
class Scene;
class UiMgr;


enum class WeaponModes
{
	Hammer,
	//Arrow,
	Magic,
	COUNT,
};

class Player : public SpriteObj
{
public:
	enum class States
	{
		None = -1,
		Idle,
		Move,
		Jump,
	};
protected:
	//Sprite sprite;
	Animator animator;
	States currState;

	Vector2f direction;
	Vector2f lastDirection;
	float speed;
	
	WeaponModes weaponMode;

public:
	Player() :currState(States::None), speed(200.f), 
			  direction(1.f, 0.f), lastDirection(1.f, 0.f), 
		      weaponMode(WeaponModes::Hammer) {}
	virtual ~Player();
		
	virtual void Init() override;
	
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void UpdateIdle(float dt);
	void UpdateMove(float dt);
	void UpdateJump(float dt);

	void SetState(States newState);
	void SetWeaponModes();
	//void SetHealth(float delta) { health += delta; }
	void SetStatData(int idx);

	Vector2f GetPosition();

	//float GetDamage() const { return damage; }
	//float GetMaxHealth() { return maxHealth; }
	//float GetHealth() { return health; }

	void OnCompleteJump();
};