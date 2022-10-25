#include "SceneGame.h"
#include "SceneMgr.h"
#include "../Frameworks.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/Player.h"
#include "../Ui/UiGameMgr.h"
#include "../GameObject/Boss.h"
#include "../GameObject/HitBox.h"

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
	background->SetPos({ 0, 80 });
	
	backgroundBattom = new SpriteObj();
	backgroundBattom->SetTexture(*RESOURCE_MGR->GetTexture("graphics/game_background_battom.png"));
	backgroundBattom->SetOrigin(Origins::TC);
	backgroundBattom->SetPos({ 0, -35 });
	

	player = new Player();
	player->SetName("Player");
	player->Init();

	boss = new Boss();
	boss->SetName("Boss");
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
	backgroundBattom->Update(dt);
	player->Update(dt);
	worldView.setCenter(player->GetPos().x, player->GetPos().y - 200);

	if (Utils::OBB(player->GetHitBoxShape(), boss->GetLeftArmHitBoxShape())|| Utils::OBB(player->GetHitBoxShape(), boss->GetRightArmbodyHitBoxShape()))
	{
		cout << "hand collision" << endl;
		if (player->GetPos().x > boss->GetLeftArmHitBoxShape().getOrigin().x || player->GetPos().x > boss->GetRightArmbodyHitBoxShape().getOrigin().x)
		{
			player->SetDirection({ 1.f,0.f });
		}
		else
		{
			player->SetDirection({ -1.f,0.f });
		}
	}
}

void SceneGame::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	background->Draw(window);
	window.setView(worldView);
	boss->Draw(window);
	backgroundBattom->Draw(window);
	player->Draw(window);
	
}
