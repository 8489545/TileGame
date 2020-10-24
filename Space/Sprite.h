#pragma once
class Texture;
class Sprite : public Object
{
	LPD3DXSPRITE m_pSp;
	Texture* m_Texture;


public:
	Sprite();
	~Sprite();

	RECT m_Rect;
	D3DXVECTOR3 m_Center;
public:
	bool Init(std::wstring fileName);

public:

	static Sprite* Create(std::wstring fileName);
	void Render() override;

public:
	int A, R, G, B;
};