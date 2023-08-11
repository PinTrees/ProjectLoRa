#include "pch.h"
#include "SettingMgr.h"

#include "CResMgr.h"
#include "CSound.h"


SINGLE_HEADER(SettingMgr);



SettingMgr::SettingMgr()
	: mFindPathType(FIND_PATH_TYPE::ASTAR)
{
}

SettingMgr::~SettingMgr()
{
}


void SettingMgr::SetVolume(int vol)
{
	 mVolume = vol;

     const map<wstring, CRes*>& mapSounds = CResMgr::GetI()->GetSoundResource();

     for (auto iter = mapSounds.begin(); iter != mapSounds.end(); ++iter)
     {
         wstring soundName = iter->first;
         CSound* soundResource = (CSound*)(iter->second);

         soundResource->SetVolume(mVolume);
     }
}

void SettingMgr::Init()
{
}
