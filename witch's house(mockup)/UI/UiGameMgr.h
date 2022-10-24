#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"
#include "../DataTable/StringTable.h"

class Scene;

class UiGameMgr :public UiMgr
{
protected:
	

public:
	UiGameMgr(Scene* scene);
	virtual ~UiGameMgr();

	virtual void Init() override;
	virtual void Release() override;
	void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};