#pragma once
#include "CObject.h"
class CGuidMissile :
    public CObject
{

public:
    CGuidMissile();
    ~CGuidMissile();

public:
    virtual void Update() override;
};

