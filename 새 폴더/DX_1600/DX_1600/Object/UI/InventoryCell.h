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

	// �� �������� �Ծ����� player���� �˷��ִ� bool
	Items GetItemState() { return item; }

	// �������� ���� �� Items�� �ٲ��ִ� �Լ�
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

	// �����۵� ���� �� ������ �ִٰ� �ش� ������ ������ Ȱ��ȭ
};