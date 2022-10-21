#include "Player.h"
#include "../FrameWork/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/Pickup.h"
#include "../Framework/Framework.h"
#include "../Framework/SoundMgr.h"
#include "../Scenes/SceneMgr.h"
#include "../Ui/UiGameMgr.h"

Player::Player()
	:speed(300), accelation(500), deaccelation(500), fireMode(FireModes::PISTOL), exp(0.f)
{
}

Player::~Player()
{
}

void Player::Init()
{
	SetOrigin(Origins::MC);
	SpriteObj::Init();

	level = 1;
	exp = 0.f;
	SetStatData(level);

	scene = SCENE_MGR->GetCurScene();
	UiMgr = scene->GetUiMgr();
}

void Player::Reset()
{
	direction = { 1.f,0.f };
	velocity = { 0.f,0.f };
	level = 1;
	exp = 0.f;
	fireMode = FireModes::PISTOL;
	SetStatData(level);
}

void Player::Update(float dt)
{
	SpriteObj::Update(dt);

	RenderWindow& window = FRAMEWORK->GetWindow();
	Vector2i mousePos = (Vector2i)InputMgr::GetMousePos();
	Vector2f mouseWorldPos = scene->ScreenToWorldPos(mousePos);

	look = Utils::Normalize(mouseWorldPos);

	sprite.setRotation(Utils::Angle(look));
	hitbox.setRotation(Utils::Angle(look));

	direction.x = InputMgr::GetAxisRaw(Axis::Horizontal);
	direction.y = InputMgr::GetAxisRaw(Axis::Vertical);
	
	//����
	velocity += direction * accelation * dt;
	if ( Utils::Magnitude(velocity) > speed )
	{
		velocity = Utils::Normalize(velocity) * speed;
	}

	//����
	if (Utils::Magnitude(direction) == 0.f)
	{
		velocity = { 0.f, 0.f };
	}

	if ( direction.x == 0.f )
	{
		if ( velocity.x > 0.f )
		{
			velocity.x -= deaccelation * dt;
			if ( velocity.x < 0.f )
				velocity.x = 0.f;
		}
		if ( velocity.x < 0.f )
		{
			velocity.x += deaccelation * dt;
			if ( velocity.x > 0.f )
				velocity.x = 0.f;
		}
	}

	if ( direction.y == 0.f )
	{
		if ( velocity.y > 0.f )
		{
			velocity.y -= deaccelation * dt;
			if ( velocity.y < 0.f )
				velocity.y = 0.f;
		}
		if ( velocity.y < 0.f )
		{
			velocity.y += deaccelation * dt;
			if ( velocity.y > 0.f )
				velocity.y = 0.f;
		}
	}

	Translate(velocity * dt);


	// test
	if (InputMgr::GetKeyDown(Keyboard::P))
	{
		cout << "level: " << level << endl <<
			"reqUireExp: " << reqUireExp << endl <<
			"health: " << health << endl <<
			"damage: " << damage << endl <<
			"exp: " << exp << endl;
	}

	if ( InputMgr::GetMouseDown(Mouse::Button::Right) )
	{
		SetShootType();
	}

	// die
	if (health <= 0.f)
	{
		cout << "die" << endl;
	}

	// level up, max level 10
	if (level <= 10 && exp >= reqUireExp)
	{
		SOUND_MGR->Play("sound/levelup.wav");
		exp -= reqUireExp;
		level++;
		SetStatData(level);
		cout << "level up!! " << level << endl;
	}
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
}

void Player::ResetVelocity()
{
	velocity = Vector2f(0, 0);
}

void Player::SetShootType()
{
	fireMode = (FireModes)((int)fireMode + 1);
	if (fireMode == FireModes::COUNT)
		fireMode = FireModes::PISTOL;
}

void Player::OnPickupItem(Pickup* item)
{
	switch ( item->GetType() )
	{
	case Pickup::Types::Health:
		
		health += item->GetValue();
		if ( health >= maxHealth )
			health = maxHealth;
		break;
	case Pickup::Types::Exp:
		exp += item->GetValue();
		break;
	}
}

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

Vector2f Player::GetLook()
{
	return look;
}
