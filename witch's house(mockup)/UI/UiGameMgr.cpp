#include "UiGameMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneGame.h"
#include "../Framework/InputMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StringTable.h"
#include <string>

UiGameMgr::UiGameMgr(Scene* scene)
	:UiMgr(scene)
{
}

UiGameMgr::~UiGameMgr()
{
}

void UiGameMgr::Init()
{
	Vector2i WindowSize = FRAMEWORK->GetWindowSize();
	
	auto stringTable = DATATABLE_MGR->Get<StringTable>(DataTable::Types::String);
	stringTable->SetLanguage(StringTable::getCurrentLang());
	

	UiMgr::Init();
}

void UiGameMgr::Release()
{
	UiMgr::Release();
}

void UiGameMgr::Reset()
{
	
}

void UiGameMgr::Update(float dt)
{
	UiMgr::Update(dt);
}

void UiGameMgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}
