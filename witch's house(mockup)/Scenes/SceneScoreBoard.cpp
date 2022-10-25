#include "SceneScoreBoard.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/TextObj.h"
#include "../Framework/SoundMgr.h"
#include "../Framework/Framework.h"

SceneScoreBoard::SceneScoreBoard()
	:Scene(Scenes::ScoreBoard)
{
}

SceneScoreBoard::~SceneScoreBoard()
{
}

void SceneScoreBoard::Init()
{


	/*obj2 = new Object();
	obj2->SetHitbox({ 0,0,100,100 });
	obj1->SetPos({ 300,100 });
	AddGameObj(obj2);*/
	
	for ( auto obj : objList )
	{
		obj->Init();
	}
}

void SceneScoreBoard::Release()
{
}

void SceneScoreBoard::Enter()
{
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(false);
}

void SceneScoreBoard::Exit()
{
	
}

void SceneScoreBoard::Update(float dt)
{
	
	if ( InputMgr::GetKeyDown(Keyboard::Space) )
	{
		SCENE_MGR->ChangeScene(Scenes::Game);
	}
	if ( InputMgr::GetKeyDown(Keyboard::F1) )
	{
		for ( Object* obj : objList )
		{
			obj->SetDevMode(false);
		}
	}
	if ( InputMgr::GetKeyDown(Keyboard::F2) )
	{
		for ( Object* obj : objList )
		{
			obj->SetDevMode(true);
		}
	}
	Scene::Update(dt);
}

void SceneScoreBoard::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}
