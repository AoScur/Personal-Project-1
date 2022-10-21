#include "UiScoreBoardMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneGame.h"
#include "../Framework/InputMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StringTable.h"
#include <string>

UiScoreBoardMgr::UiScoreBoardMgr(Scene* scene)
	:UiMgr(scene)
{
}

UiScoreBoardMgr::~UiScoreBoardMgr()
{
}

void UiScoreBoardMgr::Init()
{
	Vector2i WindowSize = FRAMEWORK->GetWindowSize();

	UiMgr::Init();
}

void UiScoreBoardMgr::Release()
{
	UiMgr::Release();
}

void UiScoreBoardMgr::Reset()
{
	UiMgr::Reset();
}

void UiScoreBoardMgr::Update(float dt)
{
	UiMgr::Update(dt);
	

	
}

void UiScoreBoardMgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}