#pragma once

class inventory
{
public:
	enum ItemState
	{
		NONE,
		HELMET,
		KINGBULLET,
		SCOPE,
		SPEEDBOOTS
	};

	inventory();
	~inventory();

	void Update();
	void PostRender();

	// 인벤 채우는 함수, 1채우기 시작해서 해당 _invenCell의 _isFilled = true이면 다음 _invenCell으로 이동
	void FillItem(ItemState value);
	
	void FillInventory(InventoryCell::Items item);

	// 인벤 지우는 함수, 맨 앞 cell부터 버림, 바로 뒤 cell의 State를 가져오고 맨 뒤의 cell은 None으로 만들기
	void DropItems();

	// _invenCell1의 Items 를 넘겨주는 함수
	InventoryCell::Items GetInvenState();

	//void SetOn(bool value) { _on = value; }

	shared_ptr<Collider> GetTransform() { return _collider; }

	void Cell0MoveX(Vector2 value) { _inventory[0]->GetTransform()->SetPosition(value); }
	void Cell1MoveX(Vector2 value) { _inventory[1]->GetTransform()->SetPosition(value); }
	void Cell2MoveX(Vector2 value) { _inventory[2]->GetTransform()->SetPosition(value); }
	void Cell3MoveX(Vector2 value) { _inventory[3]->GetTransform()->SetPosition(value); }

private:
	//아이템 먹을 시 순서대로 각 이벤토리 칸에 해당 아이템의 정보 불러오기 
	vector<shared_ptr<class InventoryCell>> _inventory;


	shared_ptr<Collider> _collider;

	ItemState itemState = ItemState::NONE;

	int count = 0;
};