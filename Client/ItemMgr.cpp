#include "pch.h"
#include "ItemMgr.h"

#include "Item.h"


SINGLE_HEADER(ItemMgr);


ItemMgr::ItemMgr()
	: mArrItem{}
{

}

ItemMgr::~ItemMgr()
{

}


void ItemMgr::Init()
{
	mArrItem[(UINT)ITEM_TYPE::ITEM_1] = new Item;
	mArrItem[(UINT)ITEM_TYPE::ITEM_2] = new Item;
	mArrItem[(UINT)ITEM_TYPE::ITEM_3] = new Item;
}
