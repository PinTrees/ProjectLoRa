#include "pch.h"
#include "SettingMgr.h"

#include "CResMgr.h"
#include "CSound.h"


SINGLE_HEADER(SettingMgr);



SettingMgr::SettingMgr()
	: mFindPathType(FIND_PATH_TYPE::ASTAR)
    , mbMonsterHpbarActive(false)
{
}

SettingMgr::~SettingMgr()
{
}


void SettingMgr::Init()
{
}


void SettingMgr::SetVolume(int vol)
{
	 mVolume = vol;

     const map<wstring, CRes*>& mapSounds = CResMgr::GetI()->GetSoundResource();

     for (auto iter = mapSounds.begin(); iter != mapSounds.end(); ++iter)
     {
         wstring soundName = iter->first;

         if (soundName == L"Sound_BGM")
             continue;

         CSound* soundResource = (CSound*)(iter->second);

         soundResource->SetVolume(mVolume);
     }
}

void SettingMgr::SetBGMVolume(int vol)
{
    mBgmVolume = vol;

    CSound* soundResource = CResMgr::GetI()->FindSound(L"Sound_BGM");
    soundResource->SetVolume(mBgmVolume);
}
