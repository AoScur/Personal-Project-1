#include "Boss.h"
#include "../FrameWork/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "HitBox.h"

Boss::Boss()
	:currState(States::None)
{
}

Boss::~Boss()
{
}

void Boss::Init()
{
	animator.SetTarget(&sprite);
	Utils::SetOrigin(sprite, Origins::BC);
	sprite.setScale(6, 4);

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaAppear"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaFrontIdle"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaFrontAttackLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaFrontAttackRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaLeftFascination"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaLeftFascinationSuccess"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaStrikeDown"));


	SetState(States::Appear);
	animator.Play("KoopaFrontIdle");

	bodyHitBox = new HitBox();
	leftArmHitBox = new HitBox();
	rightArmHitBox = new HitBox();


 	SpriteObj::Init();	

}

void Boss::Reset()
{
}

void Boss::Update(float dt)
{
	SpriteObj::Update(dt);
	
	switch (currState)
	{
	case Boss::States::Appear:
		UpdateAppear(dt);
		break;
	case Boss::States::Idle:
		UpdateIdle(dt);
		break;
	case Boss::States::AttackLeft:
		UpdateAttackLeft(dt);
		break;
	case Boss::States::AttackRight:
		UpdateAttackRight(dt);
		break;
	case Boss::States::StrikeDown:
		UpdateStrikeDown(dt);
		break;
	case Boss::States::Fascination:
		UpdateFascination(dt);
		break;
	case Boss::States::FascinationSuccess:
		UpdateFascinationSuccess(dt);
		break;
	}
	animator.Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::Key::F5))
	{ 
		bodyHitBox->SetDevMode(true);
		leftArmHitBox->SetDevMode(true);
		rightArmHitBox->SetDevMode(true);
	}
	
	
	FloatRect bossSize = sprite.getGlobalBounds();
	bodyHitBox->SetHitbox({ 0,0,bossSize.width * 0.3f,bossSize.height * 0.7f });
	bodyHitBox->SetPos(GetPos());
	leftArmHitBox->SetHitbox({ 0,0,100.f,70.f });
	leftArmHitBox->SetPos({ GetPos().x+300,GetPos().y-120 });
	rightArmHitBox->SetHitbox({ 0,0,100.f,70.f });
	rightArmHitBox->SetPos({ GetPos().x - 300,GetPos().y - 120 });

}

void Boss::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	bodyHitBox->Draw(window);
	leftArmHitBox->Draw(window);
	rightArmHitBox->Draw(window);
}

void Boss::SetState(States newState)
{
	//if (currState == newState)
	//	return;	
	switch (currState)
	{
	case Boss::States::Appear:
		animator.Play("KoopaAppear");
		break;
	case Boss::States::Idle:
		animator.Play("KoopaFrontIdle");
		break;
	case Boss::States::AttackLeft:
		animator.Play("KoopaFrontAttackLeft");
		break;
	case Boss::States::AttackRight:
		animator.Play("KoopaFrontAttackRight");
		break;
	case Boss::States::StrikeDown:
		animator.Play("KoopaLeftFascination");
		break;
	case Boss::States::Fascination:
		animator.Play("KoopaLeftFascinationSuccess");
		break;
	case Boss::States::FascinationSuccess:
		animator.Play("KoopaStrikeDown");
		break;
	}
}

void Boss::UpdateAppear(float dt)
{
	SetPos({ 0.f, -400.f });
	SetState(States::Appear);
	Vector2f velocity(0.f, -700.f);
	Vector2f gravity(0.f, 2000.f);
	velocity += gravity * dt;
	Vector2f delta = velocity * dt;
	Translate(delta);
	if (velocity.y>0.f&&GetPos().y<100.f)
	{
		SetPos({ 0.f, 100.f });
	}
}

void Boss::UpdateIdle(float dt)
{
	SetPos({ 0.f, 100.f });
	SetState(States::Idle);
}

void Boss::UpdateAttackLeft(float dt)
{
	SetState(States::AttackLeft);
}

void Boss::UpdateAttackRight(float dt)
{
	SetState(States::AttackRight);
}

void Boss::UpdateStrikeDown(float dt)
{
	SetState(States::StrikeDown);
}

void Boss::UpdateFascination(float dt)
{
	SetState(States::Fascination);
}

void Boss::UpdateFascinationSuccess(float dt)
{
	SetState(States::FascinationSuccess);
}
