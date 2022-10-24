#include "Player.h"
#include "../FrameWork/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/SoundMgr.h"
#include "../Scenes/SceneMgr.h"
#include "../Ui/UiGameMgr.h"

Player::~Player()
{
}

void Player::Init()
{
	Vector2i size = FRAMEWORK->GetWindowSize();
	animator.SetTarget(&sprite);
	position = {0.f, 0.f };
	sprite.setScale(2, 2);

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioIdleLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioIdleRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioMoveLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioMoveRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioJumpLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioJumpRight"));
	{
		AnimationEvent ev;
		ev.clipId = "MarioJumpLeft";
		ev.frame = 7;
		ev.onEvnet = bind(&Player::OnCompleteJump, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "MarioJumpRight";
		ev.frame = 7;
		ev.onEvnet = bind(&Player::OnCompleteJump, this);
		animator.AddEnvet(ev);
	}
	SetState(States::Idle);

	SpriteObj::Init();
}

void Player::Reset()
{
	direction = { 1.f,0.f };
	weaponMode = WeaponModes::Hammer;
}

void Player::Update(float dt)
{
	SpriteObj::Update(dt);

	RenderWindow& window = FRAMEWORK->GetWindow();
	if (InputMgr::GetKeyDown(Keyboard::Key::B))
	{

	}
	direction.x = 0.f;
	direction.x += InputMgr::GetAxisRaw(Axis::Horizontal);
	if (InputMgr::GetKeyDown(Keyboard::Key::Space))
	{
		currState = States::Jump;
	}
	switch (currState)
	{
	case Player::States::Idle:
		UpdateIdle(dt);
		break;
	case Player::States::Move:
		UpdateMove(dt);
		break;
	case Player::States::Jump:
		UpdateJump(dt);
		break;
	}
	animator.Update(dt);
	if (!Utils::EqualFloat(direction.x, 0.f))
	{
		lastDirection = direction;
	}

 	Translate(direction*speed * dt);
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::UpdateIdle(float dt)
{
	if (!Utils::EqualFloat(direction.x, 0.f))
	{
		SetState(States::Move);
		return;
	}
}

void Player::UpdateMove(float dt)
{
	if (Utils::EqualFloat(direction.x, 0.f))
	{
		SetState(States::Idle);
		return;
	}
	if (!Utils::EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "MarioMoveRight" : "MarioMoveLeft");
	}
}

void Player::UpdateJump(float dt)
{

}

void Player::SetState(States newState)
{
	if (currState == newState)
		return;
	currState = newState;
	switch (currState)
	{
	case Player::States::Idle:
		animator.Play(lastDirection.x > 0.f ? "MarioIdleRight" : "MarioIdleLeft");
		break;
	case Player::States::Move:
		animator.Play((direction.x > 0.f) ? "MarioMoveRight" : "MarioMoveLeft");
		break;
	case Player::States::Jump:
		animator.Play((lastDirection.x > 0.f) ? "MarioJumpRight" : "MarioJumpLeft");
		break;
	}
}

void Player::SetWeaponModes()
{
	weaponMode = (WeaponModes)((int)weaponMode + 1);
	if (weaponMode == WeaponModes::COUNT)
		weaponMode = WeaponModes::Hammer;
}

void Player::SetStatData(int idx)
{
	//maxHealth = pst.LoadHealth(idx);
	//health = pst.LoadHealth(idx);
	//damage = pst.LoadDamage(idx);
	//maxHealth = 100;
	//health = 100;
	//damage = 10;
}

//void Player::SetShootType()
//{
//	fireMode = (FireModes)((int)fireMode + 1);
//	if (fireMode == FireModes::COUNT)
//		fireMode = FireModes::PISTOL;
//}

//void Player::OnHitZombie(Zombie* zombie)
//{
//	if (Utils::OBB(hitbox, zombie->GetHitbox()))
//	{
//		SetHealth(-FRAMEWORK->GetRealDT() * 10.f * zombie->GetDamage());
//	}
//}

Vector2f Player::GetPosition()
{
	return position;
}

void Player::OnCompleteJump()
{
	SetState(States::Idle);
}

