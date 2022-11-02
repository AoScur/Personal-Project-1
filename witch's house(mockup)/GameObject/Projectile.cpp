#include "Projectile.h"
#include "../Framework/ResourceMgr.h"
#include "HitBox.h"
#include "Underling.h"

Projectile::Projectile()
	:duration(10.f)
{
}

Projectile::~Projectile()
{
}

void Projectile::Fire(Vector2f direction)
{
	enabled = true;
	timer = 0.f;
	speed = 100.f;
	this->direction = direction;
	animator.Play("MarioFireBall");
}

void Projectile::Init()
{
	animator.SetTarget(&sprite);
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioFireBall"));
	animator.Play("MarioFireBall");
	hitbox = new HitBox();
	SetActive(false);
	SpriteObj::Init();
}

void Projectile::Release()
{
}

void Projectile::Update(float dt)
{
	timer += dt;
	if (timer > duration)
	{
		enabled = false;
	}
	Translate(direction * speed * dt);
	animator.Update(dt);
	hitbox->SetHitbox({ GetGlobalBounds() });
	hitbox->SetPos(GetPos());

	//for (Underling* underling : *underlings)
	//{
	//	if (underling->GetActive())
	//	{
	//		if (Utils::OBB(hitbox->GetHitbox(), underling->GetHitBoxShape()))
	//		{
	//			underling->OnHitFireBall(this);
	//			SetActive(false);
	//			break;
	//		}
	//	}
	//}
	SpriteObj::Update(dt);
}

void Projectile::Draw(RenderWindow& window)
{
	hitbox->Draw(window);
	SpriteObj::Draw(window);
}
