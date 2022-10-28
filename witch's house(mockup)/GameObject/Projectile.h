#pragma once
#include "SpriteObj.h"
#include "../Framework/Animator.h"
#include "HitBox.h"
#include <list>

class Underling;

class Projectile : public SpriteObj
{
protected:
	float speed;
	Vector2f direction;
	float duration;
	float timer;
	Animator animator;
	HitBox* hitbox;

	std::list<Underling*>* underlings;


public:
	Projectile();
	virtual ~Projectile();

	void SetUnderlingList(std::list<Underling*>* list) { underlings = list; }
	void Fire(Vector2f direction);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

