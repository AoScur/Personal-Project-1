#pragma once
#include "Scene.h"
#include "../GameObject/Object.h"

class SceneScoreBoard :public Scene
{

protected:
	Object* obj1;
	Object* obj2;
public:
	SceneScoreBoard();
	virtual ~SceneScoreBoard();

	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

