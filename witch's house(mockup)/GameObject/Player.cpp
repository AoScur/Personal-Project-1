#include "Player.h"
#include "../FrameWork/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/SoundMgr.h"
#include "../Scenes/SceneMgr.h"
#include "../Ui/UiGameMgr.h"
#include "HitBox.h"
#include "Projectile.h"
#include "Underling.h"

Player::~Player()
{
}

void Player::Init()
{
	Vector2i size = FRAMEWORK->GetWindowSize();
	animator.SetTarget(&sprite);
	position = {0.f, 0.f };
	sprite.setScale(2, 2);
	isJump = false;

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioIdleLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioIdleRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioMoveLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioMoveRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioJumpLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioJumpRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioAttackHammerLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioAttackHammerRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioAttackMagicLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MarioAttackMagicRight"));

	{
 		AnimationEvent ev;
		ev.clipId = "MarioAttackHammerLeft";
		ev.frame = 11;
		ev.onEvnet = bind(&Player::OnCompleteJump, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "MarioAttackHammerRight";
		ev.frame = 11;
		ev.onEvnet = bind(&Player::OnCompleteJump, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "MarioAttackMagicLeft";
		ev.frame = 9;
		ev.onEvnet = bind(&Player::OnCompleteJump, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "MarioAttackMagicRight";
		ev.frame = 9;
		ev.onEvnet = bind(&Player::OnCompleteJump, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "MarioAttackMagicLeft";
		ev.frame = 5;
		ev.onEvnet = bind(&Player::ShowFireBall, this);
		animator.AddEnvet(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "MarioAttackMagicRight";
		ev.frame = 5;
		ev.onEvnet = bind(&Player::ShowFireBall, this);
		animator.AddEnvet(ev);
	}

	SetState(States::Idle);

	hitbox = new HitBox();

	for (int i = 0; i < 20; ++i)
	{
		auto fireball = new Projectile();
		fireball->Init();
		fireball->SetActive(false);
		unuseFireBalls.push_back(fireball);
	}

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

	auto it = useFireBalls.begin();
	while (it != useFireBalls.end())
	{
		(*it)->Update(dt);
		if (!(*it)->GetActive())
		{
			unuseFireBalls.push_back(*it);
			it = useFireBalls.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::A))
	{
		SetWeaponModes(WeaponModes::Hammer);
		damage = 100;
		cout << "무기종류 :" << (int)weaponMode << endl;
	}
	if (InputMgr::GetKeyDown(Keyboard::Key::S))
	{
		SetWeaponModes(WeaponModes::Magic);
		damage = 200;
		cout << "무기종류 :" << (int)weaponMode << endl;
	}
	if (!(currState == States::Jump)&&!(currState==States::Attack))
	{
		direction.x = 0.f;
		Vector2f curpos = GetPos();
		direction.x += InputMgr::GetAxisRaw(Axis::Horizontal);
		
		if (InputMgr::GetKeyDown(Keyboard::Key::Space))
		{
			SetState(States::Jump);
		}
	}

	if (!(currState == States::Jump)&&InputMgr::GetKeyDown(Keyboard::Key::Q))
	{
		SetState(States::Attack);
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
	case Player::States::Attack:
		UpdateAttack(dt);
		break;
	}

	animator.Update(dt);
	if (!Utils::EqualFloat(direction.x, 0.f))
	{
		lastDirection = direction;
	}
	Translate(direction*speed * dt);

	if (InputMgr::GetKeyDown(Keyboard::Key::F5))
		hitbox->SetDevMode(true);
	hitbox->SetHitbox({ GetGlobalBounds() });
	hitbox->SetPos(GetPos());


}

void Player::Draw(RenderWindow& window)
{
	hitbox->Draw(window);
	SpriteObj::Draw(window);

	for (auto fireball : useFireBalls)
	{
		fireball->Draw(window);
	}
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
	if (!isJump)
	{
		battom = position.y;
	}
	isJump = true;
	speed = 0;
	velocity.x = lastDirection.x == 1 ? abs(velocity.x) : -abs(velocity.x);
	velocity += gravity * dt;
	Vector2f delta = velocity * dt;
	Translate(delta);
	//SetPos(position);

	if (battom-position.y<0.2f&&velocity.y>0.f)
	{
		SetPos({position.x, battom});
		velocity = Vector2f(300.f, -800.f);
		gravity = Vector2f(0.f, 2000.f);
		speed = 200.f;
		isJump = false;
		OnCompleteJump();
	}

	
}

void Player::UpdateAttack(float dt)
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
	case Player::States::Attack:
		switch (weaponMode)
		{
		case WeaponModes::Hammer:
			animator.Play((lastDirection.x > 0.f) ? "MarioAttackHammerRight" : "MarioAttackHammerLeft");
			break;
		case WeaponModes::Magic:
			animator.Play((lastDirection.x > 0.f) ? "MarioAttackMagicRight" : "MarioAttackMagicLeft");
			break;
		}		
	}
}

void Player::SetWeaponModes(WeaponModes mode)
{
	weaponMode = mode;
}

void Player::SetStatusData(int idx)
{
	/*maxHealth = pst.LoadHealth(idx);
	health = pst.LoadHealth(idx);
	damage = pst.LoadDamage(idx);*/
	maxHealth = 500;
	curHealth = 500;
}

void Player::OnHitUnderling(Underling* underling)
{
	SetHealth(-FRAMEWORK->GetRealDT() * 10.f * underling->GetDamage());
}


void Player::OnCompleteJump()
{
	SetState(States::Idle);
}

void Player::ShowFireBall()
{
	if (unuseFireBalls.empty())
		return;

	auto fireball = unuseFireBalls.front();
	unuseFireBalls.pop_front();
	useFireBalls.push_back(fireball);

	Vector2f fireBallPosition;
	fireBallPosition.x = (lastDirection.x < 0.f) ? GetPos().x - 35.f : GetPos().x + 35.f;
	fireBallPosition.y = GetPos().y - 27.f;

	fireball->SetPos(fireBallPosition);
	fireball->Fire(lastDirection);
}
