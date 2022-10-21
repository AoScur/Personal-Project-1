#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "../GameObject/Object.h"

class Player;

using namespace std;
using namespace sf;

class UiMgr;

enum class Scenes
{
	Title,
	Menu,
	Game,
	ScoreBoard,
};

class Scene
{
protected:
	Scenes type;
	list<Object*> objList;
	UiMgr* uiMgr;

	View worldView;
	View UiView;
	
public:
	Scene(Scenes type);
	virtual ~Scene();

	virtual void Init() = 0;
	virtual void Release();

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	Texture* GetTexture(string id);

	const View& GetWorldView() { return worldView; }
	const View& GetUiView() { return UiView; }

	Vector2f ScreenToWorldPos(Vector2i screenPos);
	Vector2f ScreenToUiPos(Vector2i screenPos);

	Object* FindGameObj(string name);

	void AddGameObj(Object* obj)
	{
		objList.push_back(obj);
	}

	UiMgr* GetUiMgr()
	{
		return uiMgr;
	}
};