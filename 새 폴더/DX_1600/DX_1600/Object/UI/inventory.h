#pragma once

class inventory
{
public:
	inventory();
	~inventory();

private:
	//������ ���� �� ������� �� �̺��丮 ĭ�� �ش� �������� ���� �ҷ����� 
	shared_ptr<class InventoryCell> _invenCell1;
	shared_ptr<class InventoryCell> _invenCell2;
	shared_ptr<class InventoryCell> _invenCell3;
	shared_ptr<class InventoryCell> _invenCell4;
};