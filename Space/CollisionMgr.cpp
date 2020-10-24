#include "stdafx.h"
#include "CollisionMgr.h"


CollisionMgr::CollisionMgr()
{
}


CollisionMgr::~CollisionMgr()
{
}

bool CollisionMgr::MouseWithBoxSize(Object* obj)
{
	POINT Mouse;
	if (obj->m_Tag != "UI")
	{
		Mouse.x = (LONG)INPUT->GetLocalMousePos().x;
		Mouse.y = (LONG)INPUT->GetLocalMousePos().y;
	}
	else
	{
		Mouse.x = (LONG)INPUT->GetMousePos().x;
		Mouse.y = (LONG)INPUT->GetMousePos().y;
	}

	if(PtInRect(&obj->m_Collision,Mouse))
	{
		return true;
	}

	return false;
}