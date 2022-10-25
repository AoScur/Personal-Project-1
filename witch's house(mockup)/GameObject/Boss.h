#pragma once
#include "SpriteObj.h"
#include "../Framework/Animator.h"
#include "HitBox.h"


class Boss :    public SpriteObj
{
public:
	enum class States
	{
		None = -1,
		Idle,
		Attack,
		Left,
	};
protected:
	Animator animator;
	States currState;

	HitBox* bodyHitBox;
	HitBox* leftArmHitBox;
	HitBox* rightArmbodyHitBox;


public:
	Boss();
	virtual ~Boss();

	virtual void Init() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void SetState(States newState);

	const RectangleShape& GetBodyHitBoxShape() { return bodyHitBox->GetHitbox(); }
	const RectangleShape& GetLeftArmHitBoxShape() { return leftArmHitBox->GetHitbox(); }
	const RectangleShape& GetRightArmbodyHitBoxShape() { return rightArmbodyHitBox->GetHitbox(); }

	void UpdateIdle(float dt);
	void UpdateAttack(float dt);
	void UpdateLeft(float dt);

	Vector2f GetPosition() { return position; }
};

