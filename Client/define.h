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

#define DEBUG true


enum class GROUP_TYPE
{
	PARALLAX,
	DEFAULT,

	BACK,
	TILE,

	ENV,
	GOLD,


	PLAYER,
	MONSTER,
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
	CREATE_OBJECT,		// 오브젝트 생성
	DELETE_OBJECT,		// 오브젝트 삭제
	SCENE_CHANGE,		// 씬 체인지 이벤트
	CHANGE_AI_STATE,	// AI 상태 변경

	END,
};

enum class BULLET_STATE
{

};





// Monster State
enum class MONSTER_STATE
{
	IDLE,
	TRACE,
	Create,
	DEAD,
	ATTACK,
};


// 스테이트 패턴으로 변경 필요
enum class PLAYER_STATE
{
	NONE,
	IDLE,
	ATTACK,
	RUN,
	Die,
	DASH,
};




enum class LEVELUP_EFFECT
{
	FULL_HP_UP,				// 최대체력 증가
	REGENERATION_HP_UP,		// 체력재생 증가
	MOVE_SPEED_UP,			// 이동속도 증가
	ATK_DAMAGE_UP,			// 공격력 증가
	ATK_SPEED_UP,			// 공격속도 증가
	ATK_RANGE_UP,			// 사거리 증가
	SHOT_SPEED_UP,			// 총알속도 증가
	RELOAD_SPEED_UP,		// 장전속도 증가
	SHOT_ANGLE_UP,			// 명중률 증가
	SHOT_COUNT_UP,			// 발사총알 개수 증가
	PENETRATION_UP,			// 관통 수 증가
	SPLITCOUNT_UP,			// 분열 수 증가
	BOUNTCECOUNT_UP,		// 튕김 수 증가

	TEST_SKILL,

	END
};



