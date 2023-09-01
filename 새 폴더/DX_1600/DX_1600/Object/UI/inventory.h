#pragma once

class inventory
{
public:
	inventory();
	~inventory();

	void Update();
	void PostRender();

	// �κ� ä��� �Լ�, 1ä��� �����ؼ� �ش� _invenCell�� _isFilled = true�̸� ���� _invenCell���� �̵�
	void FillInventory(InventoryCell::Items item);

	// �κ� ����� �Լ�, �� �� cell���� ����, �ٷ� �� cell�� State�� �������� �� ���� cell�� None���� �����
	void DropItems();

	// _invenCell1�� Items �� �Ѱ��ִ� �Լ�
	InventoryCell::Items GetInvenState();

	void SetOn(bool value) { _on = value; }

	shared_ptr<Collider> GetTransform() { return _collider; }

private:
	//������ ���� �� ������� �� �̺��丮 ĭ�� �ش� �������� ���� �ҷ����� 
	vector<shared_ptr<class InventoryCell>> _inventory;

	shared_ptr<Collider> _collider;

	bool _on = false;
};