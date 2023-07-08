#include "pch.h"
#include "Gravity.h"

#include "CObject.h"
#include "RigidBody.h"

bool CGravity::_onLand = false;

CGravity::CGravity()
	:
	mpOwner(nullptr),
	_ground(false)
{

}

CGravity::~CGravity()
{

}

void CGravity::FinalUpdate()
{
	mpOwner->GetRigidBody()->SetAccelAlpha(Vec2(0.f, 1400.f));
}

void CGravity::SetOnGround(bool ground)
{
	_ground = ground;

	if (_ground)
	{
		Vec2 v = mpOwner->GetRigidBody()->GetVelocity();

		// ÀÏ¹Ý ¶¥À§
		mpOwner->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

		// ºùÆÇÀ§
		// mpOwner->GetRigidBody()->SetVelocity(Vector2(v._x, 0.f));
	}
}
