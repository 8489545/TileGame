#include"stdafx.h"
#include"MapEditScene.h"

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
#if _DEBUG
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);

#endif
	App::GetInst()->Init(800, 600, 1);
	SceneDirector::GetInst()->ChangeScene(new MapEditScene());
	App::GetInst()->Run();
	return 0;
}