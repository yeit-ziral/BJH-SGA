#include "framework.h"
#include "InventoryCell.h"
#include "inventory.h"

inventory::inventory()
{
	_invenCell1 = make_shared<InventoryCell>();
	_invenCell2 = make_shared<InventoryCell>();
	_invenCell3 = make_shared<InventoryCell>();
	_invenCell4 = make_shared<InventoryCell>();
}

inventory::~inventory()
{
}

void inventory::Update()
{
}

void inventory::PostRender()
{
}

void inventory::FillInventory(InventoryCell::Items item)
{
	if (_invenCell1->_isFilled = false)
	{
		_invenCell1->SetItemState(item);
		_invenCell1->_isFilled = true;
	}
	if (_invenCell2->_isFilled = false)
	{
		_invenCell2->SetItemState(item);
		_invenCell2->_isFilled = true;
	}
	if (_invenCell3->_isFilled = false)
	{
		_invenCell3->SetItemState(item);
		_invenCell3->_isFilled = true;
	}
	if (_invenCell4->_isFilled = false)
	{
		_invenCell4->SetItemState(item);
		_invenCell4->_isFilled = true;
	}
}

void inventory::DropItems()
{
}

InventoryCell::Items inventory::GetInvenState()
{
	return _invenCell1->GetItemState();
}
