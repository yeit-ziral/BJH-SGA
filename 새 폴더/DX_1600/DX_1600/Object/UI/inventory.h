#pragma once

class inventory
{
public:
	enum ItemState
	{
		NONE,
		HELMET,
		KINGBULLET,
		SCOPE,
		SPEEDBOOTS
	};

	inventory();
	~inventory();

	void Update();
	void PostRender();

	// �κ� ä��� �Լ�, 1ä��� �����ؼ� �ش� _invenCell�� _isFilled = true�̸� ���� _invenCell���� �̵�
	void FillItem(ItemState value);
	
	void FillInventory(InventoryCell::Items item);

	// �κ� ����� �Լ�, �� �� cell���� ����, �ٷ� �� cell�� State�� �������� �� ���� cell�� None���� �����
	void DropItems();

	// _invenCell1�� Items �� �Ѱ��ִ� �Լ�
	inventory::ItemState GetInvenState();

	//void SetOn(bool value) { _on = value; }

	shared_ptr<Collider> GetTransform() { return _collider; }

	void Cell0MoveX(Vector2 value) { _inventory[0]->GetTransform()->SetPosition(value); }
	void Cell1MoveX(Vector2 value) { _inventory[1]->GetTransform()->SetPosition(value); }
	void Cell2MoveX(Vector2 value) { _inventory[2]->GetTransform()->SetPosition(value); }
	void Cell3MoveX(Vector2 value) { _inventory[3]->GetTransform()->SetPosition(value); }

private:
	//������ ���� �� ������� �� �̺��丮 ĭ�� �ش� �������� ���� �ҷ����� 
	vector<shared_ptr<class InventoryCell>> _inventory;


	shared_ptr<Collider> _collider;

	ItemState itemState = ItemState::NONE;

	int count = 0;
};