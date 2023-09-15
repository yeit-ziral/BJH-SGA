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
}

GunInvenCell::~GunInvenCell()
{
}

void GunInvenCell::Update()
{
}

void GunInvenCell::PostRender()
{
}

void GunInvenCell::FillInven()
{
}
