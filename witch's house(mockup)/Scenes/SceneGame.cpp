#include "SceneGame.h"
#include "SceneMgr.h"
#include "../Frameworks.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/Player.h"
#include "../GameObject/Pickup.h"
#include "../GameObject/ItemGenerator.h"
#include "../Ui/UiGameMgr.h"

SceneGame::SceneGame()
	: Scene(Scenes::Game)
{

}

SceneGame::~SceneGame()
{

}

void SceneGame::Init()
{
	Release();

	uiMgr = new UiGameMgr(this);
	uiMgr->Init();


	ITEM_GEN->Init();

}

void SceneGame::Release()
{
	if (uiMgr != nullptr )
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}
	Scene::Release();
}

void SceneGame::Enter()
{

	ITEM_GEN->Release();

	//마우스 커서
	FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x, size.y);
	worldView.setCenter(0.f, 0.f);
	
	UiView.setSize(size.x, size.y);
	UiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	player->SetPos({ 0, 0 });

	player->Reset();
	uiMgr->Reset();
}

void SceneGame::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	
	//item
	ITEM_GEN->Release();

	player->Reset();


	uiMgr->Reset();
	SOUND_MGR->StopAll();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	uiMgr->Update(dt);
}

void SceneGame::Draw(RenderWindow& window)
{
	
	Scene::Draw(window);
	
	window.setView(worldView);

	uiMgr->Draw(window);
	
}
