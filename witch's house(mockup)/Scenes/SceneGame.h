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
	ObjectPool<Underling> underlings;

	Player* player;
	Boss* boss;
	
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

	void CreateUnderling(int count);
	const list<Underling*>& GetUnderlingList() { return underlings.GetUseList(); }
};