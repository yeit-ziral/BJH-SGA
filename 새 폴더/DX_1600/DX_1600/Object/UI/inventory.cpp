#include "framework.h"
#include "inventory.h"
#include "InventoryCell.h"

inventory::inventory()
{
	_collider = make_shared<RectCollider>(Vector2(200, 50));
	_collider->SetPosition({0.0f, 0.0f});

	for (int i = 0; i < 4; i++)
	{
		shared_ptr<InventoryCell> _invenCell = make_shared<InventoryCell>();

		_invenCell->GetTransform()->SetScale({ 0.1f, 0.1f });

		_invenCell->GetTransform()->SetParent(_collider->GetTransform());

		Vector2 invenScale = _invenCell->GetTransform()->GetScale();

		float PosX = _collider->GetTransform()->GetPos().x - ((-1.5f + i) * invenScale.x);

		_invenCell->GetTransform()->SetPosition(Vector2(PosX, 0.0f));

		_inventory.push_back(_invenCell);
	}
	Cell0MoveX(Vector2(-75, 0));
	Cell1MoveX(Vector2(-25, 0));
	Cell2MoveX(Vector2(+25, 0));
	Cell3MoveX(Vector2(+75, 0));
}

inventory::~inventory()
{
}

void inventory::Update()
{
	//if (!_on)
	//	return;

	if (KEY_DOWN(VK_F1))
		int a = 0;


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

void inventory::FillItem(ItemState value)
{
	if (value == ItemState::NONE)
	{
		FillInventory(InventoryCell::Items::NONE);
	}
	if (value == ItemState::HELMET)
	{
		FillInventory(InventoryCell::Items::HELMET);
	}
	if (value == ItemState::KINGBULLET)
	{
		FillInventory(InventoryCell::Items::KINGBULLET);
	}
	if (value == ItemState::SCOPE)
	{
		FillInventory(InventoryCell::Items::SCOPE);
	}
	if (value == ItemState::SPEEDBOOTS)
	{
		FillInventory(InventoryCell::Items::SPEEDBOOTS);
	}
}

void inventory::FillInventory(InventoryCell::Items item)
{
	for (int i = 0; i < _inventory.size(); i++)
	{
		if (_inventory[i]->_isFilled == false)
		{
			
			count++;

			_inventory[i]->SetItemState(item);
			_inventory[i]->_isFilled = true;
			break;
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

