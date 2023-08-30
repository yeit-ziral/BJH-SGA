#pragma once
class InventoryCell
{
public:
	InventoryCell();
	~InventoryCell();

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;

	bool _isFilled = false;

};