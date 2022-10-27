#include "Projectile.h"
#include "../Framework/ResourceMgr.h"
#include "HitBox.h"

Projectile::Projectile()
	:duration(0.f)
{
}

Projectile::~Projectile()
{
}

void Projectile::Fire()
{
	enabled = true;
	timer = 2.f;
	speed = 2000.f;
}

void Projectile::Init()
{
	animator.SetTarget(&sprite);
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioFireBall"));
	//hitbox = new HitBox();
	SpriteObj::Init();
}

void Projectile::Release()
{
}

void Projectile::Update(float dt)
{
	animator.Play("MarioFireBall");
	timer += dt;
	if (timer > duration)
	{
		enabled = false;
	}
	Translate(direction * speed * dt);
	//hitbox->SetHitbox({ GetGlobalBounds() });
	//hitbox->SetPos(GetPos());
	SpriteObj::Update(dt);
}

void Projectile::Draw(RenderWindow& window)
{
	//hitbox->Draw(window);
	SpriteObj::Draw(window);
}
