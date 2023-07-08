#pragma once

class CObejct;

class CHP
{
    friend class CObject;
private:
    CObject*    mpOwner;
    Vec2        mvOffset;
    Vec2        mvFinalPos;
    Vec2        mvSize;

    float       mFullHP;
    float       mCurHP;

public:
    void SetOffset(Vec2 _offset) { mvOffset = _offset; }
    void SetSize(Vec2 _size) { mvSize = _size; }

    void Update();
    void Render(HDC _dc);
    void FinalUpdate();

    CHP();
    ~CHP();

    CLONE(CHP);
};

