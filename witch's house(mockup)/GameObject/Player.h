#pragma once
#include "SpriteObj.h"
#include "../Framework/ObjectPool.h"
#include "../DataTable/PlayerStatTable.h"
#include "HitBox.h"
#include "../Framework/Animator.h"
#include <list>

class Pickup;
class UiMgr;
class Projectile;
class Underling;


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
		Attack,
	};
protected:
	//Sprite sprite;
	Animator animator;
	States currState;
	WeaponModes weaponMode;

	Vector2f direction;
	Vector2f lastDirection;
	Vector2f velocity { 300.f, -800.f };
	Vector2f gravity{ 0.f, 2000.f };
	bool isJump;
	float battom;

	HitBox* hitbox;

	float speed;
	float maxHealth;
	float curHealth;
	float damage;

	bool ishandcollision;

	Texture fireball;
	std::list<Projectile*> unuseFireBalls;
	std::list<Projectile*> useFireBalls;

public:
	Player() :currState(States::None), weaponMode(WeaponModes::Hammer),
			  speed(200.f), direction(1.f, 0.f), lastDirection(1.f, 0.f), ishandcollision(false)
		       {}
	virtual ~Player();
		
	virtual void Init() override;
	
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void UpdateIdle(float dt);
	void UpdateMove(float dt);
	void UpdateJump(float dt);
	void UpdateAttack(float dt);

	void SetState(States newState);
	void SetWeaponModes(WeaponModes mode);
	void SetStatusData(int idx);
	void SetSpeed(float speed) { this->speed = speed; }
	void SetDirection(Vector2f direction) { this->direction = direction; }
	void SetIsHandCollision(bool ishandcollision) {	this->ishandcollision= ishandcollision;}
	void SetHealth(float delta) { curHealth += delta; }

	const RectangleShape& GetHitBoxShape() { return hitbox->GetHitbox(); }
	bool GetIsJump() { return isJump; }
	float GetDamage() const { return damage; }
	float GetMaxHealth() { return maxHealth; }
	float GetCurHealth() { return curHealth; }

	void OnCompleteJump();

	void OnHitUnderling(Underling* underling);
	
	void ShowFireBall();
};