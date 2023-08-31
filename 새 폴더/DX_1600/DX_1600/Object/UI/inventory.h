#pragma once

class inventory
{
public:
	inventory();
	~inventory();

private:
	//아이템 먹을 시 순서대로 각 이벤토리 칸에 해당 아이템의 정보 불러오기 
	shared_ptr<class InventoryCell> _invenCell1;
	shared_ptr<class InventoryCell> _invenCell2;
	shared_ptr<class InventoryCell> _invenCell3;
	shared_ptr<class InventoryCell> _invenCell4;
};