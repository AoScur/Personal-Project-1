#include "Boss.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"

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
	sprite.setPosition({ 0.f, -380.f });
	sprite.setScale(6, 4);


	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaFrontIdle"));
	SetState(States::Idle);
	animator.Play("KoopaFrontIdle");
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
	case Boss::States::Idle:
		SetState(States::Idle);
		break;
	case Boss::States::Attack:
		SetState(States::Attack);
		break;
	case Boss::States::Left:
		SetState(States::Left);
		break;
	}
	animator.Update(dt);
}

void Boss::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Boss::SetState(States newState)
{
	//if (currState == newState)
	//	return;	
	switch (currState)
	{
	case Boss::States::Idle:
		animator.Play("KoopaFrontIdle");
		break;
	case Boss::States::Attack:
		
		break;
	case Boss::States::Left:
	
		break;
	}
}

void Boss::UpdateIdle(float dt)
{
}

void Boss::UpdateAttack(float dt)
{
}

void Boss::UpdateLeft(float dt)
{
}
