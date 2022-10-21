#include "UiMenuMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneMenu.h"
#include "../Framework/InputMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StringTable.h"
#include "../SFML-2.5.1/include/SFML/Graphics/Font.hpp"

using namespace sf;

UiMenuMgr::UiMenuMgr(Scene* scene)
	:UiMgr(scene)
{
}

UiMenuMgr::~UiMenuMgr()
{
}

void UiMenuMgr::Init()
{
	Release();

	Vector2i WindowSize = FRAMEWORK->GetWindowSize();

	auto stringTable = DATATABLE_MGR->Get<StringTable>(DataTable::Types::String);
	stringTable->SetLanguage(StringTable::getCurrentLang());
	
	//gameStrat
	gameStart = new TextObj();	
	gameStart->SetText(stringTable->Get("Menu_Game"));
	gameStart->GetSfmlText().setCharacterSize(40);
	gameStart->SetOrigin(Origins::MC);
	gameStart->SetPos({ WindowSize.x * 0.5f,WindowSize.y * 0.7f });
	UiObjList.push_back(gameStart);

	UiMgr::Init();
}

void UiMenuMgr::Release()
{
	UiMgr::Release();
}

void UiMenuMgr::Reset()
{
	gameStart->SetActive(true);
}

void UiMenuMgr::Update(float dt)
{
	UiMgr::Update(dt);
	auto stringTable = DATATABLE_MGR->Get<StringTable>(DataTable::Types::String);

}

void UiMenuMgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}
