#pragma once
#include "SpriteObj.h"
#include "../Framework/Animator.h"
#include "HitBox.h"

class Projectile : public SpriteObj
{
protected:
	float speed;
	Vector2f direction;
	float duration;
	float timer;
	Animator animator;
	HitBox* hitbox;


public:
	Projectile();
	virtual ~Projectile();

	void Fire();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

