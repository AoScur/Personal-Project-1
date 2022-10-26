#include "SceneGame.h"
#include "SceneMgr.h"
#include "../Frameworks.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../GameObject/Player.h"
#include "../Ui/UiGameMgr.h"
#include "../GameObject/Boss.h"
#include "../GameObject/HitBox.h"
#include "../Scenes/SceneGame.h"

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
	//뷰 조정
	worldView.setCenter(player->GetPos().x, player->GetPos().y - 200);

	if (worldView.getCenter().x - worldView.getSize().x * 0.5f < background->GetGlobalBounds().left)
	{
		worldView.setCenter(background->GetGlobalBounds().left + worldView.getSize().x * 0.5f, player->GetPos().y - 200);
	}
	else if (worldView.getCenter().x + worldView.getSize().x * 0.5f > background->GetGlobalBounds().left+ background->GetGlobalBounds().width)
	{
		worldView.setCenter(background->GetGlobalBounds().left+ background->GetGlobalBounds().width - worldView.getSize().x * 0.5f, player->GetPos().y - 200);
	}
	//보스 손과 충돌 처리
	if (!player->GetIsJump())
	{
		if (Utils::OBB(player->GetHitBoxShape(), boss->GetLeftArmHitBoxShape()))
		{			
			player->SetIsHandCollision(true);
			if (player->GetPos().x > boss->GetLeftArmHitBoxShape().getGlobalBounds().left + boss->GetLeftArmHitBoxShape().getGlobalBounds().width*0.5)
			{
				player->SetPos({ boss->GetLeftArmHitBoxShape().getGlobalBounds().left + boss->GetLeftArmHitBoxShape().getGlobalBounds().width + player->GetGlobalBounds().width * 0.5f, player->GetPos().y });
				cout << "1" << endl;
			}
			else
			{
				player->SetPos({ boss->GetLeftArmHitBoxShape().getGlobalBounds().left - player->GetGlobalBounds().width * 0.5f, player->GetPos().y });
				cout << "2" << endl;
			}
			//cout << "collision" << endl;
		}
		if (Utils::OBB(player->GetHitBoxShape(), boss->GetRightArmHitBoxShape()))
		{
			player->SetIsHandCollision(true);
			if (player->GetPos().x > boss->GetRightArmHitBoxShape().getGlobalBounds().left + boss->GetRightArmHitBoxShape().getGlobalBounds().width*0.5)
			{
				player->SetPos({ boss->GetRightArmHitBoxShape().getGlobalBounds().left + boss->GetRightArmHitBoxShape().getGlobalBounds().width + player->GetGlobalBounds().width * 0.5f, player->GetPos().y });
				cout << "3" << endl;
			}
			else
			{
				player->SetPos({ boss->GetRightArmHitBoxShape().getGlobalBounds().left - player->GetGlobalBounds().width * 0.5f, player->GetPos().y });
				cout << "4" << endl;
			}
			//cout << "collision" << endl;
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
