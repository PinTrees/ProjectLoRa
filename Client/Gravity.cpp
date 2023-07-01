#include "pch.h"
#include "Gravity.h"

#include "CObject.h"
#include "RigidBody.h"

bool CGravity::_onLand = false;

CGravity::CGravity()
	:
	p_owner(nullptr),
	_ground(false)
{

}

CGravity::~CGravity()
{

}

void CGravity::FinalUpdate()
{
	p_owner->GetRigidBody()->SetAccelAlpha(Vec2(0.f, 1400.f));
}

void CGravity::SetOnGround(bool ground)
{
	_ground = ground;

	if (_ground)
	{
		Vec2 v = p_owner->GetRigidBody()->GetVelocity();

		// ÀÏ¹Ý ¶¥À§
		p_owner->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

		// ºùÆÇÀ§
		// p_owner->GetRigidBody()->SetVelocity(Vector2(v._x, 0.f));
	}
}
