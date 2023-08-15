#pragma once




class WaveMgr
{
	SINGLE(WaveMgr);

private:
	int		mCurWaveCount;


public:
	int GetCurWaveCount() { return mCurWaveCount; }


public:
	void Init();

	void CreateWave();
};

