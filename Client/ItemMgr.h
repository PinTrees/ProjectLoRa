#pragma once


class Item;


class ItemMgr
{
	SINGLE(ItemMgr);

private:
	Item* mArrItem[(UINT)ITEM_TYPE::END];


public:
	void Init();
};

