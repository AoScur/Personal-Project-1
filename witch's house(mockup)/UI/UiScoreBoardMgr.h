#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"
#include "../DataTable/StringTable.h"

class Scene;

class UiScoreBoardMgr :public UiMgr
{
protected:

public:
	UiScoreBoardMgr(Scene* scene);
	virtual ~UiScoreBoardMgr();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset();

	void Update(float dt);
	virtual void Draw(RenderWindow& window);

};