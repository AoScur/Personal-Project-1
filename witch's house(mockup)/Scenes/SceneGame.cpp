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
#include "../GameObject/underling.h"
#include "../GameObject/Projectile.h"

//void OnCreateFireBall(Projectile* fireball)
//{
//	SceneGame* scene = (SceneGame*)SCENE_MGR->GetScene(Scenes::Game);
//	fireball->SetUnderlingList(scene->GetUnderlingList());
//	fireball->Init();
//}

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

	underlings.Init();
	for (auto unerling : underlings.GetUnuseList())
	{
		unerling->SetPlayer(player);
	}

	fireBalls.Init();
}

void SceneGame::Release()
{
	fireBalls.Release();
	underlings.Release();
	Scene::Release();
}

void SceneGame::Enter()
{
	player->Reset();
	boss->Reset();
	fireBalls.Reset();
	underlings.Reset();
	/*underling->Reset();*/


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
	fireBalls.Reset();
	underlings.Reset();
	/*underling->Reset();*/
	/*auto it = underlings.begin();
	while (it != underlings.end())
	{
		objList.remove(*it);
		delete* it;

		it = underlings.erase(it);
	}*/
}

void SceneGame::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		Vector2f pos;
		pos.x = Utils::RandomRange(200, 400);
		pos.y = 0.f;

		auto mob = underlings.Get();
		mob->SetPos(pos);
	}


	Vector2i size = FRAMEWORK->GetWindowSize();
	Scene::Update(dt);
	background->Update(dt);
	boss->Update(dt);
	backgroundBattom->Update(dt);
	player->Update(dt);
	for (auto& fireball : fireBalls.GetUseList())
	{
		fireball->Update(dt);
	}
	fireBalls.Update(dt);

	for (auto& underling : underlings.GetUseList())
	{
		underling->Update(dt);
	}
	underlings.Update(dt);

	//for (auto it = underlings.begin(); it != underlings.end(); it++)
	//{
	//	(*it)->Update(dt);
	//}
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
	//해머, 쫄몹 충돌처리
	for (auto it = underlings.GetUseList().begin();it != underlings.GetUseList().end();++it)
	{
		if (Utils::OBB(player->GetHammerHitBoxShape(), (*it)->GetHitBoxShape()))
		{
			(*it)->SetHealth(-player->GetDamage());
			cout << (*it)->GetCurHealth() << endl;
		}
	}

	//파이어볼, 쫄몹 충돌처리
	for (auto it = underlings.GetUseList().begin();it != underlings.GetUseList().end();++it)
	{
		for (auto it2 = fireBalls.GetUseList().begin();it2 != fireBalls.GetUseList().end();++it2)
		{
			if (Utils::OBB((*it2)->GetHitBoxShape(), (*it)->GetHitBoxShape()))
			{
				(*it2)->SetActive(false);
				(*it)->SetHealth(-player->GetDamage());
				cout << (*it)->GetCurHealth() << endl;
			}
		}
	}
	for (auto it = underlings.GetUseList().begin();it != underlings.GetUseList().end();++it)
	{
		if ((*it)->GetCurHealth() <= 0)
		{
			(*it)->SetActive(false);
		}
	}

	for (auto it = objList.begin(); it != objList.end(); )
	{
		if (!(*it)->GetActive())
		{
			delete (*it);
			it = objList.erase(it);
		}
		else
			it++;
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
	for (auto it = objList.begin(); it != objList.end(); it++)
	{
		(*it)->Draw(window);
	}

	for (auto& underling : underlings.GetUseList())
	{
		underling->Draw(window);
	}
	for (auto& fireball : fireBalls.GetUseList())
	{
		fireball->Draw(window);
	}
	
}
