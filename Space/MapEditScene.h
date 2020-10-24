#pragma once
template<class T>

void Button(Object* button, T func);

class MapEditScene : public Scene
{
	Sprite* m_Palette;
	Sprite* m_Panel;

	Sprite* m_ActiveTile;

	int Row;
	int Column;

	Vec2 m_PrevSize;
	Vec2 m_TileSize;
	Vec2 m_GridSize;

	bool m_isCollision;
	bool m_HideGrid;
	bool m_DrawMode;

	std::vector<Sprite*>m_Vertical;
	std::vector<Sprite*>m_Horizontal;

	TextMgr* m_SizeX;
	TextMgr* m_SizeY;
	TextMgr* m_GridSizeX;
	TextMgr* m_GridSizeY;

	Sprite* m_SizeXPlusButton;
	Sprite* m_SizeXMinusButton;

	Sprite* m_SizeYPlusButton;
	Sprite* m_SizeYMinusButton;

	Sprite* m_GridSizeXPlusButton;
	Sprite* m_GridSizeXMinusButton;

	Sprite* m_GridSizeYPlusButton;
	Sprite* m_GridSizeYMinusButton;

	Sprite* m_ChangePaletteButton;

	struct Tile
	{
	public:
		Sprite* tile;
		std::string type;
		Vec2 pos;
	};

public:
	MapEditScene();
	~MapEditScene();

	std::vector<Tile*>m_Map;

	std::wstring m_PaletteFilePath;
	std::string m_PaletteType;

	void Init();
	void Release();

	void ButtonAction();
	void DrawTile();

	void ChangePalette(std::wstring filename);
	void OpenPalette();

	void Update(float deltaTime, float Time);
	void Render();
};

template<class T>
inline void Button(Object* button, T func)
{
	if (button)
	{
		if (CollisionMgr::GetInst()->MouseWithBoxSize(button) && INPUT->GetButtonDown())
		{
			func();
			INPUT->ButtonDown(false);
		}
	}
}
