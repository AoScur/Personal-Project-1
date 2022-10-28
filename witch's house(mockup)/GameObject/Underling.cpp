#include "Underling.h"
#include "../Framework/ResourceMgr.h"
#include "HitBox.h"
#include "Player.h"
#include "../Framework/InputMgr.h"
#include "Projectile.h"

Underling::Underling()
	: speed(50.f), maxHp(50), health(200), damage(5)
{
}

Underling::~Underling()
{
}

void Underling::Init(Player* player)
{
 	animator.SetTarget(&sprite);
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("UnderlingMoveLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("UnderlingMoveRight"));
	
	this->player = player;
	hitbox = new HitBox();

	SpriteObj::Init();
}

void Underling::Reset()
{
}

void Underling::Update(float dt)
{
	SpriteObj::Update(dt);
	direction.x = 0.f;
	direction = Utils::Normalize(player->GetPos() - GetPos());
	direction.y = 0.f;
	Translate(direction * this->speed * dt);
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "UnderlingMoveRight" : "UnderlingMoveLeft");
	}
	if (!Utils::EqualFloat(direction.x, 0.f))
	{
		lastDirection = direction;
	}
	animator.Update(dt);
	if (InputMgr::GetKeyDown(Keyboard::Key::F5))
		hitbox->SetDevMode(true);
	hitbox->SetHitbox({ GetGlobalBounds() });
	hitbox->SetPos(GetPos());

	//플레이어 충돌
	if (Utils::OBB(hitbox->GetHitbox(), player->GetHitBoxShape()))
	{
		player->OnHitUnderling(this);
	}
}

void Underling::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	hitbox->Draw(window);
}

void Underling::OnHitFireBall(Projectile* fireball)
{
	SetHealth(-player->GetDamage());
}