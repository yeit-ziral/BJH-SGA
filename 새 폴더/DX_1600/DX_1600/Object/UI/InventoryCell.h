#pragma once
class InventoryCell
{
public:
	InventoryCell();
	~InventoryCell();

	void Update();
	void PostRender();

	// �� �������� �Ծ����� player���� �˷��ִ� bool

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	bool _isFilled = false;

	// �����۵� ���� �� ������ �ִٰ� �ش� ������ ������ Ȱ��ȭ
};