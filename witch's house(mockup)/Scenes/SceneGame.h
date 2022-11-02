#pragma once
#include "Scene.h"
#include <list>
#include "../Framework/ObjectPool.h"

class Player;
class Boss;
class Underling;
class Projectile;
class SpriteObj;
class Pickup;

class SceneGame : public Scene
{
protected:
	SpriteObj* background;
	SpriteObj* backgroundBattom;

	//Underling* underling;
	ObjectPool<Projectile> fireBalls;
	ObjectPool<Underling> underlings;

	Player* player;
	Boss* boss;
	
public:
	SceneGame();
	virtual ~SceneGame();

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	ObjectPool<Underling>& GetUnderlingPool() { return underlings; }
	ObjectPool<Projectile>& GetFireBallPool() { return fireBalls; }

};