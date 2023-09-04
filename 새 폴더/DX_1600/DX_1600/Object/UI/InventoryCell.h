#pragma once
class InventoryCell
{
public:
	enum Items
	{
		NONE,
		HELMET,
		KINGBULLET,
		SCOPE,
		SPEEDBOOTS
	};
	InventoryCell();
	~InventoryCell();

	void Update();
	void PostRender();

	// 각 아이템을 먹었는지 player에게 알려주는 bool
	Items GetItemState() { return item; }

	// 아이템을 먹을 때 Items를 바꿔주는 함수
	void SetItemState(Items itemState) { item = itemState; }

	bool _isFilled = false;

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	Items item = Items::NONE;

	shared_ptr<class Helmet> _helmet;
	shared_ptr<class KingBullet> _kingBullet;
	shared_ptr<class Scope> _scope;
	shared_ptr<class SpeedBoots> _speedBoots;

	// 아이템들 정보 다 가지고 있다가 해당 아이템 먹을시 활성화
};