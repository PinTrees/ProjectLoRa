#pragma once

#define SINGLE_HEADER(type) type* type::pInst = nullptr;
#define SINGLE(type) private:								\
						static type* pInst;					\
					 public:								\
						static type* GetI()					\
						{									\
							if(pInst == nullptr)			\
								pInst = new type;			\
							return pInst;					\
						}									\
						static void Dispose()				\
						{									\
							if(pInst != nullptr)			\
								 delete pInst;				\
							pInst = nullptr;				\
						}									\
						private:							\
								type();						\
								~type();


#define DT CTimeMgr::GetI()->GetfDT()
#define DELTATIME CTimeMgr::GetI()->GetDT()

#define CLONE(type) type* Clone() {return new type(*this);}


#define KEY_CHECK( key , state) CKeyMgr::GetI()->GetKeyState( key ) == state
#define KEY_HOLD(key) KEY_CHECK(key,KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key,KEY_STATE::AWAY )
#define KEY_NONE(key) KEY_CHECK(key,KEY_STATE::NONE )
#define	MOUSE_POS CKeyMgr::GetI()->GetMousePos()
#define PI 3.14159265358979323846f

#define SELECT_GDI(_dc,TYPE) SelectGDI __UNREFERENCED = SelectGDI(_dc, TYPE)

#define TILE_SIZE 32
#define TILE_SIZE_RENDER 64

#define DEBUG CSystemMgr::GetI()->GetDebug()

// --------------------------------------
// Engine 
// --------------------------------------
enum class GROUP_TYPE
{
	BACKGROUND,
	DEFAULT,

	BACK,
	TILE,

	GROUND_PLAYER,

	SHADOW,

	ENV,
	GOLD,

	PLAYER,
	MONSTER,
	
	BOSS,

	PROJ_PLAYER,
	PROJ_MONSTER,

	EFFECT,

	UI,

	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	MAIN,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	RED,
	END,
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,		// ������Ʈ ����
	DELETE_OBJECT,		// ������Ʈ ����
	SCENE_CHANGE,		// �� ü���� �̺�Ʈ
	CHANGE_AI_STATE,	// AI ���� ����

	END,
};

enum class RECT_DIRECTION
{
	LEFT,
	TOP,
	BOTTOM,
	RIGHT
};



enum class FIND_PATH_TYPE
{
	ASTAR,
	JPS,
	JPS_B,
};


// Monster State
enum class MONSTER_STATE
{
	IDLE,
	TRACE,
	Create,
	DEAD,
	ATTACK,
	HIT,

	SKILLATK,
};


// ������Ʈ �������� ���� �ʿ�
enum class PLAYER_STATE
{
	NONE,
	IDLE,
	ATTACK,
	RUN,
	DIE,
	DASH,
};


// ���� Enum ��� ���� - wstring UID �� ����
enum class SKILL_TYPE
{
	ENERGY_BALL,
	THUNDER,
	CIRCLING_BALL,
	ICE_BOLT,
	HOLYAREA,
	GRENADE,
	CROSS_DAGGER,
	BOOMERANG,
	COMBAT_BALL,
	END,
};




// ���� Enum ��� ���� - wstring UID �� ����
enum class ITEM_TYPE
{
	ITEM_1,
	ITEM_2,
	ITEM_3,
	END,
};


enum class STATEUP_TYPE
{
	FULL_HP_UP,				// �ִ�ü�� ����
	REGENERATION_HP_UP,		// ü����� ����
	MOVE_SPEED_UP,			// �̵��ӵ� ����
	ATK_DAMAGE_UP,			// ���ݷ� ����
	ATK_SPEED_UP,			// ���ݼӵ� ����
	ATK_RANGE_UP,			// ��Ÿ� ����
	SHOT_SPEED_UP,			// �Ѿ˼ӵ� ����
	RELOAD_SPEED_UP,		// �����ӵ� ����
	SHOT_ANGLE_UP,			// ���߷� ����
	SHOT_COUNT_UP,			// �߻��Ѿ� ���� ����
	PENETRATION_UP,			// ���� �� ����
	SPLITCOUNT_UP,			// �п� �� ����
	BOUNTCECOUNT_UP,		// ƨ�� �� ����

	END
};


enum class MONSTER_TYPE
{
	SHORT,
	LONG,
	BOSS,

	LOCK,
	ELITE,

	END
};
