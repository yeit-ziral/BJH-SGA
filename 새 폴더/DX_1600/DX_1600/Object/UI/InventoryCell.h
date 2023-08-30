#pragma once
class InventoryCell
{
public:
	InventoryCell();
	~InventoryCell();

	void Update();
	void PostRender();

	// 각 아이템을 먹었는지 player에게 알려주는 bool

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	bool _isFilled = false;

	// 아이템들 정보 다 가지고 있다가 해당 아이템 먹을시 활성화
};