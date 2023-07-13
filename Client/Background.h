#pragma once
#include "CObject.h"


class CTexture;




// �� Ŭ������ ���� ��� ������Ʈ �Դϴ�.
// ī�޶��� ��ǥ�� �������� ī�޶� ������ŭ ������ �˴ϴ�.
// ������Ʈ�� ������ �� Bitmap DC�� ���� ��׶��� �̹����� ���� 
class Background
	: public CObject
{
private:
	CTexture* mParallaxTex;		// Background Texture;


public:
	HDC GetParallaxDC();		


public:
<<<<<<< Updated upstream
	void Render(HDC dc, Vec2 ltPos, Vec2 size);
=======
	void Render(HDC dc, Vect2 ltPos, Vect2 size);
>>>>>>> Stashed changes
	void CreateParallaxTexture(int width, int height);	// Create Background Texture;


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	CLONE(Background);


public:
	Background();
	~Background();
};