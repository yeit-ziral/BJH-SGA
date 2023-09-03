#include "framework.h"
#include "InventoryCell.h"
#include "inventory.h"

inventory::inventory()
{
	_collider = make_shared<RectCollider>(Vector2(200, 50));
	_collider->SetPosition({0.0f, 0.0f});

	for (int i = 0; i < 4; i++)
	{
		shared_ptr<InventoryCell> _invenCell = make_shared<InventoryCell>();

		_invenCell->GetTransform()->SetParent(_collider->GetTransform());

		Vector2 invenScale = _invenCell->GetTransform()->GetScale();

		float PosX = _collider->GetTransform()->GetWorldPosition().x - ((-1.5f + i) * invenScale.x);

		_invenCell->GetTransform()->SetPosition(Vector2(PosX, 0.0f));

		_inventory.push_back(_invenCell);
	}

}

inventory::~inventory()
{
}

void inventory::Update()
{
	//if (!_on)
	//	return;

	_collider->Update();

	for (auto cell : _inventory)
	{
		cell->Update();
	}
}

void inventory::PostRender()
{

	_collider->Render();

	for (auto cell : _inventory)
	{
		cell->PostRender();
	}
}

void inventory::FillInventory(InventoryCell::Items item)
{
	for (int i = 0; i < 4; i++)
	{
		if (_inventory[i]->_isFilled == false)
		{
			_inventory[i]->SetItemState(item);
			_inventory[i]->_isFilled = true;
			return;
		}
	}
}

void inventory::DropItems()
{
	if (_inventory[0]->_isFilled == false)
		return;

	for (int i = 0; i < 3; i++)
	{
		_inventory[i]->SetItemState(_inventory[i + 1]->GetItemState());
		_inventory[i]->_isFilled = false;
	}
	_inventory[3]->SetItemState(InventoryCell::Items::NONE);
	_inventory[3]->_isFilled = false;
}

InventoryCell::Items inventory::GetInvenState()
{
	return _inventory[0]->GetItemState();
}
