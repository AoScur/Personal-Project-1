#pragma once
#include "SpriteObj.h"
#include "../Framework/Animator.h"
#include "HitBox.h"


class Boss : public SpriteObj
{
public:
	enum class States
	{
		None = -1,
		Appear,
		Idle,
		AttackLeft,
		AttackRight,
		StrikeDown,
		Fascination,
		FascinationSuccess,
	};
protected:
	Animator animator;
	States currState;

	HitBox* bodyHitBox;
	HitBox* leftArmHitBox;
	HitBox* rightArmHitBox;


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
	const RectangleShape& GetRightArmHitBoxShape() { return rightArmHitBox->GetHitbox(); }

	void UpdateAppear(float dt);
	void UpdateIdle(float dt);
	void UpdateAttackLeft(float dt);
	void UpdateAttackRight(float dt);
	void UpdateStrikeDown(float dt);
	void UpdateFascination(float dt);
	void UpdateFascinationSuccess(float dt);


	Vector2f GetPosition() { return position; }
};

