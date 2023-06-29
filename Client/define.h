#pragma once

#define SINGLE(type) public:								\
						static type* GetI()					\
						{									\
							static type mgr;				\
							return &mgr;					\
						}\
						private:\
								type();\
								~type();


#define fDT CTimeMgr::GetI()->GetfDT()
#define DELTATIME CTimeMgr::GetI()->GetDT()

#define KEY_CHECK( key , state) CKeyMgr::GetI()->GetKeyState( key ) == state
#define KEY_HOLD(key) KEY_CHECK(key,KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key,KEY_STATE::AWAY )
#define KEY_NONE(key) KEY_CHECK(key,KEY_STATE::NONE )

#define PI 3.1415926535f

#define SELECT_GDI(_dc,TYPE) SelectGDI __UNREFERENCED = SelectGDI(_dc, TYPE)




enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,

	END = 32,
};
enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,

};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

