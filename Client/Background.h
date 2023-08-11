#pragma once
#include "CObject.h"


class CTexture;




// 이 클래스는 씬의 배경 오브젝트 입니다.
// 카메라의 좌표를 기준으로 카메라 영역만큼 렌더링 됩니다.
// 오브젝트를 생성한 후 Bitmap DC를 통해 백그라운드 이미지를 설정 
class Background
	: public CObject
{
private:
	CTexture* mParallaxTex;		// Background Texture;


public:
	HDC GetParallaxDC();		


public:
	void Render(HDC dc, Vect2 ltPos, Vect2 size);
	void CreateParallaxTexture(int width, int height);	// Create Background Texture;


public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

	CLONE(Background);


public:
	Background();
	virtual ~Background() override;
};