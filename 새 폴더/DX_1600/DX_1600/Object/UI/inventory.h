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

private:
	//������ ���� �� ������� �� �̺��丮 ĭ�� �ش� �������� ���� �ҷ����� 
	shared_ptr<class InventoryCell> _invenCell1;
	shared_ptr<class InventoryCell> _invenCell2;
	shared_ptr<class InventoryCell> _invenCell3;
	shared_ptr<class InventoryCell> _invenCell4;
};