#include "UiMgr.h"

UiMgr::UiMgr(Scene* scene)
    :parentScene(scene)
{
}

UiMgr::~UiMgr()
{
}

void UiMgr::Init()
{
    Object::Init();
    for ( auto UiObj : UiObjList )
    {
        UiObj->Init();
    }
}

void UiMgr::Release()
{
    Object::Release();
    for ( auto UiObj : UiObjList )
    {
        UiObj->Release();
    }
}

void UiMgr::Reset()
{
    Object::Reset();
    for ( auto UiObj : UiObjList )
    {
        UiObj->Reset();
    }
}

void UiMgr::SetPos(const Vector2f& pos)
{
    Vector2f delta = pos - position;
    for ( auto UiObj : UiObjList )
    {
        UiObj->Translate(delta);
    }
    position = pos;
}

void UiMgr::Update(float dt)
{
    if ( !enabled )
    {
        return;
    }

    for ( auto UiObj : UiObjList )
    {
        if ( UiObj->GetActive() )
        {
            UiObj->Update(dt);
        }
    }
}

void UiMgr::Draw(RenderWindow& window)
{
    if ( !enabled )
    {
        return;
    }
    for ( auto UiObj : UiObjList )
    {
        if ( UiObj->GetActive())
        {
            UiObj->Draw(window);
        }
    }
}
