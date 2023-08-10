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

	void Play(bool _bLoop = false);			// �Ϲ� ���
	void PlayToBGM(bool _bLoop = false);	// BGM ���� ���

	void Stop(bool _bReset = false);

	void SetVolume(float _fVolume);			// ���� ���� (0 ~ 100)
	void SetPosition(float _fPosition); // �������� ��ġ ����  0 ~ 100 ����


private:
	bool LoadWaveSound(const wstring& _strPath);
	int GetDecibel(float _fVolume);


public:
	CSound();
	virtual ~CSound() override;
};

