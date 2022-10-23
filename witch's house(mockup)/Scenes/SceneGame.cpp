#include "SceneGame.h"
#include "SceneMgr.h"
#include "../Frameworks.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/Player.h"
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

	player = new Player();
	player->SetName("Player");
	player->Init();
	

}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
		//마우스 커서
	FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x, size.y);
	worldView.setCenter(player->GetPos().x, player->GetPos().y);

	player->Reset();
}

void SceneGame::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	
	//item
	player->Reset();
	SOUND_MGR->StopAll();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	player->Update(dt);

	worldView.setCenter(player->GetPos());
}

void SceneGame::Draw(RenderWindow& window)
{
	
	Scene::Draw(window);
	
	window.setView(worldView);
	player->Draw(window);
	
}
