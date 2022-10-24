#include "SceneGame.h"
#include "SceneMgr.h"
#include "../Frameworks.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/Player.h"
#include "../Ui/UiGameMgr.h"
#include "../GameObject/Boss.h"

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

	background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/game_background.png"));
	background->SetOrigin(Origins::BC);
	background->SetPos({ 0, 175 });
	
	player = new Player();
	player->SetName("Player");
	player->Init();

	boss = new Boss();
	player->SetName("Boss");
	boss->Init();
	

}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	player->Reset();
	boss->Reset();
		//마우스 커서
	FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
	Vector2i size = FRAMEWORK->GetWindowSize();
	worldView.setSize(size.x, size.y);
	//worldView.setCenter(0.f, 0.f);
	

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
	Vector2i size = FRAMEWORK->GetWindowSize();
	Scene::Update(dt);
	background->Update(dt);
	boss->Update(dt);
	player->Update(dt);
	cout <<"p :" << player->GetPosition().x << endl;
	cout << "b :" << boss->GetPosition().x << endl;
	worldView.setCenter(player->GetPos().x, player->GetPos().y - 200);
}

void SceneGame::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	background->Draw(window);
	window.setView(worldView);
	boss->Draw(window);
	player->Draw(window);
	
}
