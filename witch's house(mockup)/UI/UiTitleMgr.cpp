#include "UiTitleMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Scenes/Scene.h"
#include "../Scenes/SceneTitle.h"
#include "../Framework/InputMgr.h"
#include "../DataTable/DataTableMGR.h"
#include "../DataTable/StringTable.h"
#include "../SFML-2.5.1/include/SFML/Graphics/Font.hpp"

using namespace sf;

UiTitleMgr::UiTitleMgr(Scene* scene)
	:UiMgr(scene)
{
}

UiTitleMgr::~UiTitleMgr()
{
}

void UiTitleMgr::Init()
{
	UiMgr::Init();
	Vector2i WindowSize = FRAMEWORK->GetWindowSize();
	
	auto stringTable = DATATABLE_MGR->Get<StringTable>(DataTable::Types::String);
	stringTable->SetLanguage(StringTable::getCurrentLang());

	//title
	title = new TextObj();
	title->SetText(stringTable->Get("Title_Title"));
	title->GetSfmlText().setCharacterSize(120);
	title->SetOrigin(Origins::MC);
	title->SetPos({ WindowSize.x *0.5f,WindowSize.y *0.2f });
	UiObjList.push_back(title);
	
}

void UiTitleMgr::Release()
{
	UiMgr::Release();
}

void UiTitleMgr::Reset()
{
	UiMgr::Reset();
}

void UiTitleMgr::Update(float dt)
{
	UiMgr::Update(dt);
}

void UiTitleMgr::Draw(RenderWindow& window)
{
	window.setView(parentScene->GetUiView());
	UiMgr::Draw(window);
}
