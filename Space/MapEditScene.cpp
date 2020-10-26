#include "stdafx.h"
#include "MapEditScene.h"
#include"Map.h"

MapEditScene::MapEditScene()
{
}

MapEditScene::~MapEditScene()
{
}

void MapEditScene::Init()
{
	m_Palette = Sprite::Create(L"Painting/Map/Floor.png");
	m_Palette->SetPosition(650, 600 / 2);
	m_Palette->m_Tag = "UI";

	//------------SizeButton------------
	m_SizeXPlusButton = Sprite::Create(L"Painting/Map/Plus.png");
	m_SizeXPlusButton->SetPosition(50, 100);
	m_SizeXPlusButton->m_Tag = "UI";

	m_SizeXMinusButton = Sprite::Create(L"Painting/Map/Minus.png");
	m_SizeXMinusButton->SetPosition(100, 100);
	m_SizeXMinusButton->m_Tag = "UI";

	m_SizeYPlusButton = Sprite::Create(L"Painting/Map/Plus.png");
	m_SizeYPlusButton->SetPosition(50, 200);
	m_SizeYPlusButton->m_Tag = "UI";
		  
	m_SizeYMinusButton = Sprite::Create(L"Painting/Map/Minus.png");
	m_SizeYMinusButton->SetPosition(100, 200);
	m_SizeYMinusButton->m_Tag = "UI";
	//--------------------------------------

	//------------GridSizeButton------------
	m_GridSizeXPlusButton = Sprite::Create(L"Painting/Map/Plus.png");
	m_GridSizeXPlusButton->SetPosition(50, 300);
	m_GridSizeXPlusButton->m_Tag = "UI";

	m_GridSizeXMinusButton = Sprite::Create(L"Painting/Map/Minus.png");
	m_GridSizeXMinusButton->SetPosition(100, 300);
	m_GridSizeXMinusButton->m_Tag = "UI";

	m_GridSizeYPlusButton = Sprite::Create(L"Painting/Map/Plus.png");
	m_GridSizeYPlusButton->SetPosition(50, 400);
	m_GridSizeYPlusButton->m_Tag = "UI";

	m_GridSizeYMinusButton = Sprite::Create(L"Painting/Map/Minus.png");
	m_GridSizeYMinusButton->SetPosition(100, 400);
	m_GridSizeYMinusButton->m_Tag = "UI";
	//--------------------------------------

	//------------LayerButton------------
	m_LayerPlusButton = Sprite::Create(L"Painting/Map/Plus.png");
	m_LayerPlusButton->SetPosition(50, 500);
	m_LayerPlusButton->m_Tag = "UI";

	m_LayerMinusButton = Sprite::Create(L"Painting/Map/Minus.png");
	m_LayerMinusButton->SetPosition(100, 500);
	m_LayerMinusButton->m_Tag = "UI";
	//--------------------------------------

	m_ChangePaletteButton = Sprite::Create(L"Painting/Map/ChangePalette.png");
	m_ChangePaletteButton->SetPosition(700, 50);
	m_ChangePaletteButton->m_Tag = "UI";

	m_PaletteFilePath = L"Painting/Map/Floor.png";
	m_PaletteType = "Floor";

	m_TileSize = Vec2(25, 25);
	m_GridSize = Vec2(25, 25);
	
	m_CurrentLayer = 0;

	for (int i = 0; i < 100; i++)
	{
		Sprite* v = Sprite::Create(L"Painting/Map/Vertical.png");
		v->SetPosition(m_GridSize.x * i, App::GetInst()->m_Height / 2);
		Sprite* h = Sprite::Create(L"Painting/Map/Horizontal.png");
		h->SetPosition(App::GetInst()->m_Width / 2, m_GridSize.y * i);

		m_Vertical.push_back(v);
		m_Horizontal.push_back(h);
	}

	m_isCollision = false;
	m_HideGrid = false;
	m_DrawMode = false;

	m_SizeX = new TextMgr();
	m_SizeX->Init(32, true, false, "Arial");
	m_SizeX->SetColor(255, 255,255, 255);

	m_SizeY = new TextMgr();
	m_SizeY->Init(32, true, false, "Arial");
	m_SizeY->SetColor(255, 255, 255, 255);

	m_GridSizeX = new TextMgr();
	m_GridSizeX->Init(32, true, false, "Arial");
	m_GridSizeX->SetColor(255, 255, 255, 255);

	m_GridSizeY = new TextMgr();
	m_GridSizeY->Init(32, true, false, "Arial");
	m_GridSizeY->SetColor(255, 255, 255, 255);

	m_Layer = new TextMgr();
	m_Layer->Init(32, true, false, "Arial");
	m_Layer->SetColor(255, 255, 255, 255);

}

void MapEditScene::Release()
{
}

void MapEditScene::ButtonAction()
{
	if (!m_DrawMode)
	{
		Button(m_SizeXPlusButton, [&] { m_TileSize.x += 1; });
		Button(m_SizeXMinusButton, [&] { m_TileSize.x -= 1; });
		Button(m_SizeYPlusButton, [&] { m_TileSize.y += 1; });
		Button(m_SizeYMinusButton, [&] { m_TileSize.y -= 1; });

		Button(m_GridSizeXPlusButton, [&] { m_GridSize.x += 1; });
		Button(m_GridSizeXMinusButton, [&] { m_GridSize.x -= 1; });
		Button(m_GridSizeYPlusButton, [&] { m_GridSize.y += 1; });
		Button(m_GridSizeYMinusButton, [&] { m_GridSize.y -= 1; });

		Button(m_LayerPlusButton, [&] { m_CurrentLayer += 1; });
		Button(m_LayerMinusButton, [&] { m_CurrentLayer -= 1; });

		Button(m_ChangePaletteButton, [&] { OpenPalette(); });
	}
}

void MapEditScene::DrawTile()
{
	if (m_ActiveTile)
	{
		if ((INPUT->GetLocalMousePos().x / m_GridSize.x) * m_GridSize.x < 0 && (INPUT->GetLocalMousePos().y / m_GridSize.y) * m_GridSize.y < 0)
			m_ActiveTile->SetPosition((int)(INPUT->GetLocalMousePos().x / m_GridSize.x) * m_GridSize.x - m_GridSize.x, (int)(INPUT->GetLocalMousePos().y / m_GridSize.y) * m_GridSize.y - m_GridSize.y);
		else if ((INPUT->GetLocalMousePos().x / m_GridSize.x) * m_GridSize.x < 0)
			m_ActiveTile->SetPosition((int)(INPUT->GetLocalMousePos().x / m_GridSize.x) * m_GridSize.x - m_GridSize.x, (int)(INPUT->GetLocalMousePos().y / m_GridSize.y) * m_GridSize.y);
		else if ((INPUT->GetLocalMousePos().y / m_GridSize.y) * m_GridSize.y < 0)
			m_ActiveTile->SetPosition((int)(INPUT->GetLocalMousePos().x / m_GridSize.x) * m_GridSize.x, (int)(INPUT->GetLocalMousePos().y / m_GridSize.y) * m_GridSize.y - m_GridSize.y);
		else
			m_ActiveTile->SetPosition((int)(INPUT->GetLocalMousePos().x / m_GridSize.x) * m_GridSize.x, (int)(INPUT->GetLocalMousePos().y / m_GridSize.y) * m_GridSize.y);

		if (INPUT->GetRightButtonDown())
		{
			m_isCollision = false;
			m_ActiveTile = nullptr;
		}
	}
	if (m_ActiveTile && m_DrawMode)
	{

		for (auto& iter : m_Map)
		{
			if (iter->tile->m_Layer == m_CurrentLayer && iter->pos == Vec2(m_ActiveTile->m_Position.x / m_TileSize.x, m_ActiveTile->m_Position.y / m_TileSize.y))
			{
				m_isCollision = true;
				break;
			}
			else
				m_isCollision = false;
		}
		m_ActiveTile->m_RotationCenter = Vec2(m_TileSize.x / 2, m_TileSize.y / 2);

		if (INPUT->GetKey('R') == KeyState::DOWN)
		{
			m_ActiveTile->m_Rotation += D3DXToRadian(90);
		}


		if (INPUT->GetButtonDown() && !m_isCollision)
		{
			Tile* t = new Tile();
			Sprite* tile = Sprite::Create(m_PaletteFilePath);
			tile->m_Center = D3DXVECTOR3(0, 0, 0);
			tile->m_RotationCenter = m_ActiveTile->m_RotationCenter;
			SetRect(&tile->m_Rect, m_TileSize.x * Row + Row, m_TileSize.y * Column + Column, m_TileSize.x * (Row + 1) + Row, m_TileSize.y * (Column + 1) + Column);
			tile->m_Tag = "Tile";
			tile->m_Layer = m_CurrentLayer;
			tile->SetPosition(m_ActiveTile->m_Position.x, m_ActiveTile->m_Position.y);
			tile->m_Rotation = m_ActiveTile->m_Rotation;

			t->tile = tile;
			t->type = m_PaletteType;
			t->pos = Vec2(m_ActiveTile->m_Position.x / m_TileSize.x, m_ActiveTile->m_Position.y / m_TileSize.y);

			m_Map.push_back(t);
		}
	}
}

void MapEditScene::MovePalette()
{
	if (INPUT->GetKey('W') == KeyState::PRESS)
		m_Palette->m_Position.y -= 300 * dt;
	if (INPUT->GetKey('S') == KeyState::PRESS)
		m_Palette->m_Position.y += 300 * dt;

	if (INPUT->GetKey('A') == KeyState::PRESS)
		m_Palette->m_Position.x -= 300 * dt;
	if (INPUT->GetKey('D') == KeyState::PRESS)
		m_Palette->m_Position.x += 300 * dt;

}

void MapEditScene::ChangePalette(std::wstring filename)
{
	m_Palette = Sprite::Create(filename);
	m_Palette->SetPosition(800 / 2, 600 / 2);
	m_Palette->m_Tag = "UI";

	m_PaletteFilePath = filename;
	m_ActiveTile = nullptr;

}

void MapEditScene::OpenPalette()
{
	TCHAR filename[256] = _T("");
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = App::GetInst()->GetHwnd();
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 256;
	ofn.lpstrFilter = TEXT("ImageFiles(.png,.jpg,.bmp)\0*.png;*.jpg;*.bmp\0All Files (*.*)\0*.*\0");;
	ofn.lpstrInitialDir = TEXT("Painting\Map");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (::GetOpenFileName(&ofn) == false) return;

	ChangePalette(filename);

	LPWSTR str = PathFindFileNameW(filename);
	PathRemoveExtensionW(str);

	std::wstring type = str;
	m_PaletteType.assign(type.begin(), type.end());
}

void MapEditScene::Update(float deltaTime, float Time)
{
	Camera::GetInst()->Translate();

	m_PrevSize = m_GridSize;

	ButtonAction();
	DrawTile();
	MovePalette();

	if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Palette) && !m_DrawMode)
	{
		if (INPUT->GetButtonDown())
		{
			Row = ((int)(INPUT->GetMousePos().x) - (int)m_Palette->m_Collision.left) / 25;
			Column = ((int)INPUT->GetMousePos().y - (int)m_Palette->m_Collision.top) / 25;

			m_ActiveTile = Sprite::Create(m_PaletteFilePath);
			m_ActiveTile->m_Center = D3DXVECTOR3(0, 0, 0);
			SetRect(&m_ActiveTile->m_Collision, m_ActiveTile->m_Position.x, m_ActiveTile->m_Position.y, m_ActiveTile->m_Position.x + m_TileSize.x, m_ActiveTile->m_Position.y + m_TileSize.y);
			SetRect(&m_ActiveTile->m_Rect, m_TileSize.x * Row + Row, m_TileSize.y * Column + Column, m_TileSize.x * (Row + 1) + Row, m_TileSize.y * (Column + 1) + Column);
			INPUT->ButtonDown(false);
		}
	}


	for (auto iter = m_Map.begin();iter != m_Map.end(); )
	{
		if (CollisionMgr::GetInst()->MouseWithBoxSize((*iter)->tile) && INPUT->GetRightButtonDown() && (*iter)->type == m_PaletteType)
		{
			iter = m_Map.erase(iter);
		}
		else
			++iter;
	}

	if (INPUT->GetKey(VK_TAB) == KeyState::DOWN)
	{
		if (m_DrawMode)
			m_DrawMode = false;
		else
			m_DrawMode = true;
	}

	if (INPUT->GetKey(VK_F1) == KeyState::DOWN)
	{
		if (m_HideGrid)
		{
			for (auto& iter : m_Vertical)
			{
				iter->m_Visible = true;
			}
			for (auto& iter : m_Horizontal)
			{
				iter->m_Visible = true;
			}
			
			m_HideGrid = false;
		}
		else
		{
			for (auto& iter : m_Vertical)
			{
				iter->m_Visible = false;
			}
			for (auto& iter : m_Horizontal)
			{
				iter->m_Visible = false;
			}
			
			m_HideGrid = true;
		}
	}

	if (m_PrevSize != m_GridSize)
	{
		for (int i = 0; i < 100; i++)
		{
			m_Vertical.at(i)->SetPosition(m_GridSize.x* i, App::GetInst()->m_Height / 2);
			m_Horizontal.at(i)->SetPosition(App::GetInst()->m_Width / 2, m_GridSize.y * i);
		}
	}

	std::sort(m_Map.begin(), m_Map.end(), [&](Tile* p1, Tile* p2)
		{
			if (p1->tile->m_Layer < p2->tile->m_Layer)
				return true;
			return false;
		});
}

void MapEditScene::Render()
{

	for (auto& iter : m_Map)
	{
		iter->tile->Render();
		SetRect(&iter->tile->m_Collision, iter->tile->m_Position.x, iter->tile->m_Position.y, iter->tile->m_Position.x + m_TileSize.x, iter->tile->m_Position.y + m_TileSize.y);
	}

	for (auto& iter : m_Vertical)
	{
		if (abs(iter->m_Position.x - Camera::GetInst()->m_Position.x) > App::GetInst()->m_Width)
			iter->m_Position.x -= m_GridSize.x * 100;

		if (iter->m_Position.x < Camera::GetInst()->m_Position.x)
			iter->m_Position.x += m_GridSize.x * 100;

		iter->m_Position.y = Camera::GetInst()->m_Position.y + iter->m_Size.y / 2;

		iter->Render();
	}
	for (auto& iter : m_Horizontal)
	{
		if (abs(iter->m_Position.y - Camera::GetInst()->m_Position.y) > App::GetInst()->m_Height)
			iter->m_Position.y -= m_GridSize.y * 100;

		if (iter->m_Position.y < Camera::GetInst()->m_Position.y)
			iter->m_Position.y += m_GridSize.y * 100;

		iter->m_Position.x = Camera::GetInst()->m_Position.x + iter->m_Size.x / 2;

		iter->Render();
	}
	if (m_ActiveTile)
		m_ActiveTile->Render();

	if (!m_DrawMode)
	{
		m_Palette->Render();

		m_SizeXPlusButton->Render();
		m_SizeXMinusButton->Render();
		m_SizeYPlusButton->Render();
		m_SizeYMinusButton->Render();

		m_GridSizeXPlusButton->Render();
		m_GridSizeXMinusButton->Render();
		m_GridSizeYPlusButton->Render();
		m_GridSizeYMinusButton->Render();

		m_LayerPlusButton->Render();
		m_LayerMinusButton->Render();

		m_ChangePaletteButton->Render();

		Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
		m_SizeX->print("Tile X :" + std::to_string(((int)m_TileSize.x)), 25, 25);
		m_SizeY->print("Tile Y : " + std::to_string(((int)m_TileSize.y)), 25, 125);
		m_SizeX->print("Grid X :" + std::to_string(((int)m_GridSize.x)), 25, 225);
		m_SizeY->print("Grid Y : " + std::to_string(((int)m_GridSize.y)), 25, 325);
		m_SizeY->print("Layer : " + std::to_string(((int)m_CurrentLayer)), 25, 425);
		Renderer::GetInst()->GetSprite()->End();
	}
}
