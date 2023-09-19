#include "framework.h"
#include "GunInvenCell.h"

#include "Object/CupHead/Gun/NormalGun.h"
#include "Object/CupHead/Gun/Machinegun.h"
#include "Object/CupHead/Gun/ChargeGun.h"

GunInvenCell::GunInvenCell()
{
	_collider = make_shared<RectCollider>(Vector2(50, 50));
	_quad = make_shared<Quad>(L"Resource/UI/InventoryCell.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());

	_normalGun = make_shared<NormalGun>();
	_machineGun = make_shared<Machinegun>();
	_chargeGun = make_shared<ChargeGun>();

	 _normalGun->GetTransform()->SetParent(_collider->GetTransform());
	_machineGun->GetTransform()->SetParent(_collider->GetTransform());
	 _chargeGun->GetTransform()->SetParent(_collider->GetTransform());

	  _normalGun->GetTransform()->SetScale(Vector2(15, 15));
	 _machineGun->GetTransform()->SetScale(Vector2(15, 15));
	  _chargeGun->GetTransform()->SetScale(Vector2(15, 15));
}

GunInvenCell::~GunInvenCell()
{
}

void GunInvenCell::Update()
{
	_collider->Update();
	_transform->Update();

	if (_gunState == GunState::NONE)
	{
		_normalGun->Selected(false);
		_machineGun->Selected(false);
		_chargeGun->Selected(false);

		_isFilled = false;
	}
	if (_gunState == GunState::NORMAL)
	{
		_normalGun->Selected(true);
		_machineGun->Selected(false);
		_chargeGun->Selected(false);

		_normalGun->Update();

		_isFilled = true;
	}
	if (_gunState == GunState::MACHINE)
	{
		_normalGun->Selected(false);
		_machineGun->Selected(true);
		_chargeGun->Selected(false);

		_machineGun->Update();

		_isFilled = true;
	}
	if (_gunState == GunState::CHARGE)
	{
		_normalGun->Selected(false);
		_machineGun->Selected(false);
		_chargeGun->Selected(true);

		_chargeGun->Update();

		_isFilled = true;
	}
}

void GunInvenCell::PostRender()
{
	ImGui::Text("CellPositionX : %f", _collider->GetTransform()->GetWorldPosition());

	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();

	if (_gunState == GunState::NONE)
	{

	}
	if (_gunState == GunState::NORMAL)
	{
		_normalGun->Render();
	}
	if (_gunState == GunState::MACHINE)
	{
		_machineGun->Render();
	}
	if (_gunState == GunState::CHARGE)
	{
		_chargeGun->Render();
	}
}