#include "Boss.h"
#include "../FrameWork/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../GameObject/HitBox.h"

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
	SetPos({ 0.f, 100.f });
	sprite.setScale(6, 4);

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaFrontIdle"));
	SetState(States::Idle);
	animator.Play("KoopaFrontIdle");

	bodyHitBox = new HitBox();
	leftArmHitBox = new HitBox();
	rightArmbodyHitBox = new HitBox();


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

	if (InputMgr::GetKeyDown(Keyboard::Key::F5))
	{ 
		bodyHitBox->SetDevMode(true);
		leftArmHitBox->SetDevMode(true);
		rightArmbodyHitBox->SetDevMode(true);
	}

	FloatRect bossSize = sprite.getGlobalBounds();
	bodyHitBox->SetHitbox({ 0,0,bossSize.width * 0.3f,bossSize.height * 0.7f });
	bodyHitBox->SetPos(GetPos());
	leftArmHitBox->SetHitbox({ 0,0,100.f,70.f });
	leftArmHitBox->SetPos({ GetPos().x+300,GetPos().y-120 });
	rightArmbodyHitBox->SetHitbox({ 0,0,100.f,70.f });
	rightArmbodyHitBox->SetPos({ GetPos().x - 300,GetPos().y - 120 });

}

void Boss::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	bodyHitBox->Draw(window);
	leftArmHitBox->Draw(window);
	rightArmbodyHitBox->Draw(window);
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
