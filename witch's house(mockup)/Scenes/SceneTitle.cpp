#include "SceneTitle.h"
#include "SceneMgr.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/SoundMgr.h"
#include "../Ui/UiTitleMgr.h"

SceneTitle::SceneTitle()
	:Scene(Scenes::Title)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	Release();

	uiMgr = new UiTitleMgr(this);
	uiMgr->Init();
}

void SceneTitle::Release()
{
	if (uiMgr != nullptr)
	{
		uiMgr->Release();
		delete uiMgr;
		uiMgr = nullptr;
	}
	Scene::Release();
}

void SceneTitle::Enter()
{
	//FRAMEWORK->GetWindow().setMouseCursorVisible(false);
	//FRAMEWORK->GetWindow().setMouseCursorGrabbed(true);
	Vector2i size = FRAMEWORK->GetWindowSize();

	worldView.setSize(size.x, size.y);
	worldView.setCenter(0.f, 0.f);

	UiView.setSize(size.x, size.y);
	UiView.setCenter(size.x * 0.5f, size.y * 0.5f);
}

void SceneTitle::Exit()
{
	//FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	uiMgr->Reset();
}

void SceneTitle::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SCENE_MGR->ChangeScene(Scenes::Menu);
	}
	Scene::Update(dt);

	uiMgr->Update(dt);
}

void SceneTitle::Draw(RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
	uiMgr->Draw(window);
}
