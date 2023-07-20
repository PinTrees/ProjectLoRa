#pragma once
#include "Skill.h"




class IceBolt :
    public Skill
{
public:
    virtual bool IsStart() override;
    
    virtual void Start() override;
    virtual void ActiveUpdate() override;


public:
    IceBolt();
    virtual ~IceBolt();
};

