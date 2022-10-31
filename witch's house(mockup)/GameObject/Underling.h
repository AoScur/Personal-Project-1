#pragma once
#include "SpriteObj.h"
#include "../Framework/Animator.h"
#include "HitBox.h"

class Player;
class Projectile;

class Underling :  public SpriteObj
{
protected:
	Animator animator;

	HitBox* hitbox;
	Vector2f direction;
	Vector2f lastDirection;
	float speed;

	float maxHp;
	float health;
	float damage;

	Player* player;
public:
	Underling();
	virtual ~Underling();

	void Init();

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	const RectangleShape& GetHitBoxShape() { return hitbox->GetHitbox(); }
	float GetDamage() { return damage; }

	void SetHealth(float delta) { health = health + delta; }
	void SetPlayer(Player* player) { this->player = player; }
	void OnHitFireBall(Projectile* fireball);

};

