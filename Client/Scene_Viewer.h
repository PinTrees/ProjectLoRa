#pragma once
#include "CScene.h"

class AnimationView;
class CAnimation;
class CTexture;
class Scene_Viewer :
    public CScene
{
private:
	AnimationView*	mpAnimViewer;
	CAnimation*		mpAnimation;
	CTexture*		mpTex;
public:
	AnimationView* GetAnimObj() { return mpAnimViewer; }
	CAnimation* GetAnimation() { return mpAnimation; }
	CTexture* GetTex() { return mpTex; }


public:
	virtual void Update();
	virtual void Enter();
	virtual void Render(HDC _dc);
	virtual void Exit();

	void LoadFile();
	void LoadAnimData();
private:
	

public:
	Scene_Viewer();
	~Scene_Viewer();

};

