#pragma once

class InventoryCell;

class inventory
{
public:
	inventory();
	~inventory();

private:
	//������ ���� �� ������� �� �̺��丮 ĭ�� �ش� �������� ���� �ҷ����� 
	shared_ptr<InventoryCell> _cell1;
	shared_ptr<InventoryCell> _cell2;
	shared_ptr<InventoryCell> _cell3;
	shared_ptr<InventoryCell> _cell4;
};