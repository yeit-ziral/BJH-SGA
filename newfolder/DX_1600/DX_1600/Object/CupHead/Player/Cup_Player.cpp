#include "framework.h"
#include "Cup_Player.h"
#include "Cup_Ani.h"
#include "../Gun/Gun.h"
#include "../Gun/NormalGun.h"
#include "../Gun/Machinegun.h"
#include "../Gun/ChargeGun.h"
#include "../../UI/inventory.h"
#include "../../UI/InventoryCell.h"

using namespace tinyxml2;


Cup_Player* Cup_Player::_instance = nullptr;
Cup_Player::Cup_Player()
{
	SOUND->Add("Cup_Attack", "Resource/Sound/Attack.wav", false);
	SOUND->Add("Damaged", "Resource/Sound/drumloop.wav", false);

	_footCollider = make_shared<RectCollider>(Vector2(50.0f, 10.0f));

	_collider = make_shared<CircleCollider>(50.0f);
	_animation = make_shared<Cup_Ani>();

	_collider->GetTransform()->SetParent(GetFootTransform());
	_collider->GetTransform()->SetPosition(Vector2(0, 50));

	_animation->SetParent(_collider->GetTransform());
	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/hit_4x2.png", Vector2(4, 2), Vector2(100, 100), 0.1f);

	_normalGun = make_shared<NormalGun>();
	_machineGun = make_shared<Machinegun>();
	_chargeGun = make_shared<ChargeGun>();

	_gunSlot = make_shared<Transform>();

	_normalGun->GetTransform()->SetParent(_gunSlot);
	_normalGun->GetTransform()->SetPosition({ 50,0 });
	_machineGun->GetTransform()->SetParent(_gunSlot);
	_machineGun->GetTransform()->SetPosition({ 50,0 });
	_chargeGun->GetTransform()->SetParent(_gunSlot);
	_chargeGun->GetTransform()->SetPosition({ 50,0 });

	_inventory = make_shared<inventory>();
	//_inventory->GetTransform()->SetParent(_collider->GetTransform());


}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	if (!_isAlive)
		return;

	_gunDir = W_MOUSE_POS - _collider->GetTransform()->GetWorldPosition();
	_gunShootDir = Vector2(_gunDir.x, _gunDir.y + RandomNum(-_spread, _spread));

	if (_nowGun == NORMAL)
	{
		_normalGun->Selected(true);
		
		_machineGun->Selected(false);
		_chargeGun->Selected(false);
	}
	if (_nowGun == MACHINE)
	{
		_machineGun->Selected(true);

		_normalGun->Selected(false);
		_chargeGun->Selected(false);
	}

	if (_nowGun == CHARGE)
	{
		_chargeGun->Selected(true);

		_normalGun->Selected(false);
		_machineGun->Selected(false);
	}
	

	SetGunAngle();
	_gunSlot->SetPosition(_collider->GetTransform()->GetWorldPosition());
	_gunSlot->Update();


	Input();
	_footCollider->Update();
	_collider->Update();
	_animation->Update();
	
	_inventory->Update();
	_inventory->GetTransform()->SetPosition(Vector2(_footCollider->GetPos().x, _footCollider->GetPos().y + 100));
	
	if (KEY_PRESS('I'))
	{
		if (KEY_UP('O'))
		{
			DropItem();
		}
	}

	if (!_animation->IsActive())
		_isAlive = false;
}

void Cup_Player::Render()
{
	if (!_isAlive)
	{
		return;
	}

	_animation->Render();

	_collider->Render();

	_footCollider->Render();

	_normalGun->Render();
	_machineGun->Render();
	_chargeGun->Render();

	if(KEY_PRESS('I'))
		_inventory->PostRender();
}

void Cup_Player::PostRender()
{
	//ImGui::Text("PlayerPositionX : % f", _collider->GetTransform()->GetPos().x);
	//ImGui::Text("PlayerPositionY : % f", _collider->GetTransform()->GetPos().y);

	//ImGui::Text("GunPositionX : % f", _normalGun->GetTransform()->GetWorldPosition().x);
	//ImGui::Text("GunPositionY : % f", _normalGun->GetTransform()->GetPos().y);
	//_chargeGun->PostRender();
	
	ImGui::Text("PlayerMaxHp : %d", _maxHp);
	ImGui::Text("PlayerHp : %d", _hp);
	ImGui::Text("PlayerDamage : %d", _damage);
	ImGui::Text("PlayerAimStraitness : %d", _spread);
	ImGui::Text("Playerspeed : %f", _speed);
}


void Cup_Player::Input()
{
	if (!_isAlive)
		return;

	// �߷����� -> ���� �Ѿ˿��� �����ؾ� ��
	{
		_jumpPower -= 1000.0f * DELTA_TIME;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_footCollider->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
	}

	if(_invincible)
	{
		_invincibleTime += DELTA_TIME;
		if (_invincibleTime > 0.3f)
			_invincible = false;
	}

	if (_animation->GetState() == Cup_Ani::State::HIT)
		return;

	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

	if (KEY_DOWN('1'))
	{
		_nowGun = Gun::NORMAL;
	}
	if (KEY_DOWN('2'))
	{
		_nowGun = Gun::MACHINE;
	}
	if (KEY_DOWN('3'))
	{
		_nowGun = Gun::CHARGE;
	}

	_normalGun->Update();
	_machineGun->Update();
	_chargeGun->Update();

	Fire();

	Jump();
}

void Cup_Player::Fire() // ������ �ѱ� �� _selected = true�� �Ѹ� �߻�ǵ���
{
	if (_nowGun == Gun::NORMAL)
	{
		NormalFire();
	}
	if (_nowGun == Gun::MACHINE)
	{
		MachineFire();
	}
	if (_nowGun == Gun::CHARGE)
	{
		ChargeFire();
	}
}

void Cup_Player::Jump()
{
	if (KEY_DOWN(VK_SPACE) && _animation->GetISGround())
	{
		_jumpPower = 600.0f;
		_animation->SetIsGround(false);
	}
}

void Cup_Player::NormalFire()
{
	if (KEY_UP(VK_LBUTTON))
	{
		_normalGun->Fire(_gunShootDir);
	}
}

void Cup_Player::MachineFire()
{
	if (KEY_PRESS(VK_LBUTTON))
	{
		_machineGun->Fire(_gunShootDir);
	}
}

void Cup_Player::ChargeFire()
{
	if (KEY_PRESS(VK_LBUTTON))
	{
		
		_chargeGun->Charge();
	}
	if (KEY_UP(VK_LBUTTON))
	{
		_chargeGun->Fire(_gunShootDir);
		_chargeGun->SetChargingCount(0);
	}
}

void Cup_Player::Damaged(int damage)
{
	if (!_isAlive)
		return;

	if (!_invincible)
	{
		//CAMERA->ShakeStart(50.0f, 30.0f);
		_hp -= damage;
		_animation->DamagedEvent();
		SOUND->Play("Damaged", 0.3f);
		_invincible = true;
		_invincibleTime = 0.0f;
	}

	if (_hp < 1)
	{
		_hp = 0;
		_animation->DieEvent();
	}
}

bool Cup_Player::IsCollision_Bullets(shared_ptr<Collider> col)
{
	if (_nowGun == NORMAL)
		return _normalGun->IsCollision_Bullets(col);
	else if (_nowGun == MACHINE)
		return _machineGun->IsCollision_Bullets(col);
	else if(_nowGun == CHARGE)
		return _chargeGun->IsCollision_CBullet(col);
}

void Cup_Player::SetGrounded()
{
	if (!_isAlive)
		return;

	if (!_animation->GetISGround() && _jumpPower < 0)
	{
		_animation->SetIsGround(true);
		if (_animation->GetState() == Cup_Ani::State::HIT)
			return;
		_animation->SetStateIdle();
	}
}

bool Cup_Player::IsAlive()
{
	if (_animation->GetState() == Cup_Ani::State::GHOST)
		return false;
	else
		return true;
}

void Cup_Player::SetGunAngle()
{
	Vector2 playerToMouse = _gunDir;
	float angle = playerToMouse.Angle();
	_gunSlot->SetAngle(angle);

	/*if (MOUSE_POS.x < 0)
	{
		_normalGun->GetTransform()->SetAngle(PI);
		_normalGun->GetTransform()->SetPosition({ -50,0 });
	}
	else
	{
		_normalGun->GetTransform()->SetAngle(0);
		_normalGun->GetTransform()->SetPosition({ 50,0 });
	}*/
}

int Cup_Player::GetGunHp()
{
	if (_nowGun == Gun::NORMAL)
		return _normalGun->GetHp();
	if (_nowGun == Gun::MACHINE)
		return _machineGun->GetHp();
	if (_nowGun == Gun::CHARGE)
		return _chargeGun->GetHp();
}

int Cup_Player::GetGunMaxHp()
{
	if (_nowGun == Gun::NORMAL)
		return _normalGun->GetMaxHp();
	if (_nowGun == Gun::MACHINE)
		return _machineGun->GetMaxHp();
	if (_nowGun == Gun::CHARGE)
		return _chargeGun->GetMaxHp();
}

void Cup_Player::FixGun(int value)
{
	if (_nowGun == Gun::NORMAL)
		_normalGun->FixHp(value);
	if (_nowGun == Gun::MACHINE)
		_machineGun->FixHp(value);
	if (_nowGun == Gun::CHARGE)
		_chargeGun->FixHp(value);
}

void Cup_Player::FixAllGun(int value)
{
	_normalGun->FixHp(value);
	_machineGun->FixHp(value);
	_chargeGun->FixHp(value);
}

int Cup_Player::GetNowGunDamage()
{
	if (_nowGun == Gun::NORMAL)
		return _normalGun->GetDamage() + _damage;
	if (_nowGun == Gun::MACHINE)
		return _machineGun->GetDamage() + _damage;
	if (_nowGun == Gun::CHARGE)
		return _chargeGun->GetDamage() + _damage;
}

void Cup_Player::FillItem(Item value)
{
	if (value == Item::NONE)
	{
		_inventory->FillItem(inventory::ItemState::NONE);
	}
	if (value == Item::HELMET)
	{
		_inventory->FillItem(inventory::ItemState::HELMET);
		AddMaxHp(5);
	}
	if (value == Item::KINGBULLET)
	{
		_inventory->FillItem(inventory::ItemState::KINGBULLET);
		_damage += 5;
	}
	if (value == Item::SCOPE)
	{
		_inventory->FillItem(inventory::ItemState::SCOPE);
		FineAim(5);
	}
	if (value == Item::SPEEDBOOTS)
	{
		_inventory->FillItem(inventory::ItemState::SPEEDBOOTS);
		_speed += 300;
	}
}

void Cup_Player::DropItem()
{
	if (_inventory->GetInvenState() == inventory::ItemState::HELMET)
	{
		_maxHp -= 5;

		if (_hp > _maxHp)
			_hp = _maxHp;
		
		_inventory->DropItems();

		return;
	}
	if (_inventory->GetInvenState() == inventory::ItemState::KINGBULLET)
	{
		_damage -= 5;

		_inventory->DropItems();
		
		return;
	}
	if (_inventory->GetInvenState() == inventory::ItemState::SCOPE)
	{
		FineAim(-5);
		
		_inventory->DropItems();

		return;
	}
	if (_inventory->GetInvenState() == inventory::ItemState::SPEEDBOOTS)
	{
		_speed -= 300;

		_inventory->DropItems();

		return;
	}
}

Cup_Player::Item Cup_Player::GetItemState()
{
	if (_inventory->GetInvenState() == inventory::ItemState::HELMET)
	{
		_itemState = Item::HELMET;
	}
	if (_inventory->GetInvenState() == inventory::ItemState::KINGBULLET)
	{
		_itemState = Item::KINGBULLET;
	}
	if (_inventory->GetInvenState() == inventory::ItemState::SCOPE)
	{
		_itemState = Item::SCOPE;
	}
	if (_inventory->GetInvenState() == inventory::ItemState::SPEEDBOOTS)
	{
		_itemState = Item::SPEEDBOOTS;
	}
	if (_inventory->GetInvenState() == inventory::ItemState::NONE)
	{
		_itemState = Item::NONE;
	}

	return _itemState;
}

void Cup_Player::Revive()
{
	_hp = _maxHp;
	_isAlive = true;
	_animation->ReviveAni();
	_animation->SetState(Cup_Ani::State::IDLE);

	FixAllGun(100);
}

//void Cup_Player::InvenSetPosition(Vector2 pos)
//{
//	_inventory->GetTransform()->SetPosition(pos);
//}