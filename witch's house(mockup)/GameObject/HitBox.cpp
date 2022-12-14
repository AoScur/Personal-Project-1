#include "HitBox.h"
#include "../Framework/Utils.h"
#include "../Framework/InputMgr.h"

HitBox::HitBox()
{
}

HitBox::~HitBox()
{
}

void HitBox::SetActive(bool active)
{
}

bool HitBox::GetActive()
{
	return false;
}

void HitBox::Init()
{
}

void HitBox::Release()
{
}

void HitBox::Reset()
{
}

void HitBox::Update(float dt)
{
}

void HitBox::Draw(RenderWindow& window)
{
	if (isDevMod)
	{
		window.draw(hitbox);
	}
}

void HitBox::SetPos(const Vector2f& pos)
{
	hitbox.setPosition(pos);
}

const Vector2f& HitBox::GetPos() const
{
	return Object::GetPos();
}

void HitBox::Translate(const Vector2f delta)
{
}

void HitBox::SetHitbox(const FloatRect rect)
{
	hitBoxRect = rect;
	hitbox.setSize({ rect.width, rect.height });
	hitbox.setFillColor(Color::Red);
	hitbox.setOutlineColor(Color::Black);
	hitbox.setOutlineThickness(2.f);
	Utils::SetOrigin(hitbox, Origins::BC);
}

const RectangleShape& HitBox::GetHitbox() const
{
	return hitbox;
}

void HitBox::SetDevMode(bool dev)
{
	Object::SetDevMode(dev);
}

