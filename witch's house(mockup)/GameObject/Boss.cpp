#include "Boss.h"
#include "../FrameWork/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "HitBox.h"

Boss::Boss()
	:currState(States::Appear)
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
	sprite.setPosition({ 0.f, 1000.f });

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaAppear"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaFrontIdle"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaFrontAttackLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaFrontAttackRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaLeftFascination"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaLeftFascinationSuccess"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("KoopaStrikeDown"));
	
	{
		AnimationEvent ev;
		ev.clipId = "KoopaAppear";
		ev.frame = 7;
		ev.onEvnet = bind(&Boss::OnComplete, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "KoopaFrontAttackLeft";
		ev.frame = 12;
		ev.onEvnet = bind(&Boss::OnComplete, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "KoopaFrontAttackRight";
		ev.frame = 12;
		ev.onEvnet = bind(&Boss::OnComplete, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "KoopaStrikeDown";
		ev.frame = 8;
		ev.onEvnet = bind(&Boss::OnComplete, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "KoopaLeftFascination";
		ev.frame = 48;
		ev.onEvnet = bind(&Boss::OnCompleteFascination, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "KoopaLeftFascinationSuccess";
		ev.frame = 70;
		ev.onEvnet = bind(&Boss::OnComplete, this);
		animator.AddEnvet(ev);
	}
	SetState(States::Appear);
	//animator.Play("KoopaFrontIdle");

	bodyHitBox = new HitBox();
	leftArmHitBox = new HitBox();
	rightArmHitBox = new HitBox();


 	SpriteObj::Init();	

}

void Boss::Reset()
{
	SetPos({ 0.f, 300.f });
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
	if (currState == newState)
		return;
	currState = newState;
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
		animator.Play("KoopaStrikeDown");
		break;
	case Boss::States::Fascination:
		animator.Play("KoopaLeftFascination");
		break;
	case Boss::States::FascinationSuccess:
		animator.Play("KoopaLeftFascinationSuccess");
		break;
	}
}

void Boss::UpdateAppear(float dt)
{
 	Vector2f dir = { 0,-1 };
	Translate(dir *speed * dt);
	if (GetPos().y<110.f)
	{
		SetPos({ 0.f, 100.f });
		SetState(States::Idle);
		return;
	}
}

void Boss::UpdateIdle(float dt)
{
	SetPos({ 0.f, 100.f });
	curDelay += dt;
	if (curDelay > maxDelay)
	{
		curDelay = 0.f;
		RandomPattern();
	}
}

void Boss::UpdateAttackLeft(float dt)
{
	SetPos({ 0.f, 100.f });
}

void Boss::UpdateAttackRight(float dt)
{
	SetPos({ 0.f, 100.f });
}

void Boss::UpdateStrikeDown(float dt)
{
	SetPos({ 0.f, 100.f });
}

void Boss::UpdateFascination(float dt)
{
	SetPos({ -860.f, 100.f });
}

void Boss::UpdateFascinationSuccess(float dt)
{
	SetPos({ -860.f, 100.f });
}

void Boss::RandomPattern()
{
	SetState((States)Utils::RandomRange(2, 6));
}

void Boss::OnComplete()
{
	SetState(States::Idle);
}

void Boss::OnCompleteFascination()
{
	
}
