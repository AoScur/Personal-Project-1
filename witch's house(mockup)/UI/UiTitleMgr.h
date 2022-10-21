#pragma once
#include "UiMgr.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/SpriteObj.h"
#include "../DataTable/StringTable.h"

class Scene;

class UiTitleMgr : public UiMgr
{
protected:
	TextObj* title;
	SpriteObj* background;
	TextObj* gUide;

public:
	UiTitleMgr(Scene* scene);
	virtual ~UiTitleMgr();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Reset();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
};

