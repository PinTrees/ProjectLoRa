#pragma once
#include "SkillObj.h"


class ThunderBoom :
    public SkillObj
{
private:

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    ThunderBoom();
    ~ThunderBoom();
};

