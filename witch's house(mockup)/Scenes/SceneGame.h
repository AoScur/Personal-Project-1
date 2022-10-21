#pragma once
#include "Scene.h"
#include <list>
#include "../Framework/ObjectPool.h"
#include "../GameObject/Weapon.h"

class Player;
class VertexArrayObj;
class Zombie;
class Bullet;
class SpriteObj;
class Pickup;

class SceneGame : public Scene
{
protected:
	Player* player;
	
	VertexArrayObj* background;
	list<Zombie*> zombies;
	list<Weapon*> weapons;
	int stage;

public:
	SceneGame();
	virtual ~SceneGame();

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	list<Zombie*>* GetZombieList() { return &zombies; }
};