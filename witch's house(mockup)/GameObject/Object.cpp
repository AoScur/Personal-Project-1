#include "Object.h"
#include "../Framework/Utils.h"

int Object::objCount = 0;

Object::Object()
	:isDevMod(false)
{
	id = ++objCount;
	Init();
}

Object::~Object()
{
	Release();
}

int Object::GetObjId() const
{
	return id;
}

void Object::SetActive(bool active)
{
	enabled = active;
}

bool Object::GetActive()
{
	return enabled;
}

void Object::Init()
{
	Reset();
}

void Object::Release()
{
}

void Object::Reset()
{
	
}

void Object::SetPos(const Vector2f& pos)
{
	position = pos;
}

const Vector2f& Object::GetPos() const
{
	return position;
}

void Object::Translate(Vector2f delta)
{
	SetPos(position + delta);
}

void Object::Update(float dt)
{
}

void Object::Draw(RenderWindow& window)
{

}

void Object::SetDevMode(bool dev)
{
	isDevMod = dev;
}