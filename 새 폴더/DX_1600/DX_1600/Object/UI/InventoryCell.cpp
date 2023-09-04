#include "framework.h"
#include "InventoryCell.h"
#include "../CupHead/Items/Helmet.h"
#include "../CupHead/Items/KingBullet.h"
#include "../CupHead/Items/Scope.h"
#include "../CupHead/Items/SpeedBoots.h"

InventoryCell::InventoryCell()
{
	_collider = make_shared<RectCollider>(Vector2(50, 50));
	_quad = make_shared<Quad>(L"Resource/UI/InventoryCell.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());

		_helmet = make_shared<Helmet>();
	_kingBullet = make_shared<KingBullet>();
		 _scope = make_shared<Scope>();
	_speedBoots = make_shared<SpeedBoots>();

		_helmet->GetTransform()->SetParent(_collider->GetTransform());
	_kingBullet->GetTransform()->SetParent(_collider->GetTransform());
		 _scope->GetTransform()->SetParent(_collider->GetTransform());
	_speedBoots->GetTransform()->SetParent(_collider->GetTransform());
}

InventoryCell::~InventoryCell()
{
}

void InventoryCell::Update()
{
	_collider->Update();
	_transform->Update();

	if (item == Items::NONE)
	{
			_helmet->_isActivated = false;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = false;

		_isFilled = false;
	}
	if (item == Items::HELMET)
	{
			_helmet->_isActivated = true;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = false;

		_helmet->Update();

		_isFilled = true;
	}
	if (item == Items::KINGBULLET)
	{
			_helmet->_isActivated = false;
		_kingBullet->_isActivated = true;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = false;

		_kingBullet->Update();

		_isFilled = true;
	}
	if (item == Items::SCOPE)
	{
			_helmet->_isActivated = false;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = true;
		_speedBoots->_isActivated = false;

		_scope->Update();

		_isFilled = true;
	}
	if (item == Items::SPEEDBOOTS)
	{
			_helmet->_isActivated = false;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = true;

		_speedBoots->Update();

		_isFilled = true;
	}
}

void InventoryCell::PostRender()
{
	ImGui::Text("CellPositionX : %f", _collider->GetTransform()->GetWorldPosition());

	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();

	if (item == Items::NONE)
	{

	}
	if (item == Items::HELMET)
	{
		_helmet->Render();
	}
	if (item == Items::KINGBULLET)
	{
		_kingBullet->Render();
	}
	if (item == Items::SCOPE)
	{
		_scope->Render();
	}
	if (item == Items::SPEEDBOOTS)
	{
		_speedBoots->Render();
	}
}
