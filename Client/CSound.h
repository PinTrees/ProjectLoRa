#pragma once
#include "CRes.h"
#include "CSoundMgr.h"



class CSound :
	public CRes
{
private:
	LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
	DSBUFFERDESC			m_tBuffInfo;
	int						m_iVolume;


public:
	int Load(const wstring& _strPath);

	void Play(bool _bLoop = false);			// 일반 재생
	void PlayToBGM(bool _bLoop = false);	// BGM 으로 재생

	void Stop(bool _bReset = false);

	void SetVolume(float _fVolume);			// 볼륨 범위 (0 ~ 100)
	void SetPosition(float _fPosition); // 음악파일 위치 조정  0 ~ 100 사이


private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);


public:
	CSound();
	virtual ~CSound() override;
};

