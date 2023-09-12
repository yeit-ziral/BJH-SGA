#include "framework.h"
#include "RandomBox.h"
#include "FixingTool.h"
#include "Helmet.h"
#include "HpPotion.h"
#include "KingBullet.h"
#include "Scope.h"
#include "SpeedBoots.h"

RandomBox::RandomBox()
{
	_transform = make_shared<Transform>();

	_fixingTool = make_shared<FixingTool>();
		_helmet = make_shared<Helmet>();
	  _hpPotion = make_shared<HpPotion>();
	_kingBullet = make_shared<KingBullet>();
		 _scope = make_shared<Scope>();
	_speedBoots = make_shared<SpeedBoots>();

	_fixingTool->GetCollider()->SetParent(_transform);
		_helmet->GetCollider()->SetParent(_transform);
	  _hpPotion->GetCollider()->SetParent(_transform);
	_kingBullet->GetCollider()->SetParent(_transform);
		 _scope->GetCollider()->SetParent(_transform);
	_speedBoots->GetCollider()->SetParent(_transform);


	srand(static_cast<unsigned int>(time(nullptr)));
}

RandomBox::~RandomBox()
{
}

void RandomBox::Update()
{
	if (!_isActive)
		return;


	randNum = RandomNum(1, 7);


	if (_itemState == ItemState::NONE)
	{ }

	if (_itemState == ItemState::FIXINGTOOL)
	{
		_fixingTool->Update();
	}
	if (_itemState == ItemState::HELMET)
	{
		_helmet->Update();
	}
	if (_itemState == ItemState::HPPOTION)
	{
		_hpPotion->Update();
	}
	if (_itemState == ItemState::KINGBULLET)
	{
		_kingBullet->Update();
	}

	if (_itemState == ItemState::SCOPE)
	{
		_scope->Update();
	}

	if (_itemState == ItemState::SPEEDBOOTS)
	{
		_speedBoots->Update();
	}
}

void RandomBox::Render()
{
	if (!_isActive)
		return;

	if (_itemState == ItemState::NONE)
	{

	}

	if (_itemState == ItemState::FIXINGTOOL)
	{
		_fixingTool->Render();
	}
	if (_itemState == ItemState::HELMET)
	{
		_helmet->Render();
	}
	if (_itemState == ItemState::HPPOTION)
	{

		_hpPotion->Render();
	}
	if (_itemState == ItemState::KINGBULLET)
	{
		_kingBullet->Render();
	}

	if (_itemState == ItemState::SCOPE)
	{
		_scope->Render();
	}

	if (_itemState == ItemState::SPEEDBOOTS)
	{
		_speedBoots->Render();
	}
}

int RandomBox::RandomNum(int min, int max)
{
	int a = rand() % (max - min) + min;
	return a;
}

void RandomBox::SetRandomItem()
{
	randNum = RandomNum(1, 7);

	_itemState = ItemState(randNum);

	if (_itemState == ItemState::NONE)
	{
		_fixingTool->_isActivated = false;
			_helmet->_isActivated = false;
		  _hpPotion->_isActivated = false;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = false;
	}
	if (_itemState == ItemState::FIXINGTOOL)
	{
		_fixingTool->_isActivated = true;
			_helmet->_isActivated = false;
		  _hpPotion->_isActivated = false;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = false;

		_fixingTool->_isActivated = true;
	}
	if (_itemState == ItemState::HELMET)
	{
		_fixingTool->_isActivated = false;
			_helmet->_isActivated = true;
		  _hpPotion->_isActivated = false;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = false;

		_helmet->Render();
	}
	if (_itemState == ItemState::HPPOTION)
	{
		_fixingTool->_isActivated = false;
			_helmet->_isActivated = false;
		  _hpPotion->_isActivated = true;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = false;

		_hpPotion->Render();
	}
	if (_itemState == ItemState::KINGBULLET)
	{
		_fixingTool->_isActivated = false;
			_helmet->_isActivated = false;
		  _hpPotion->_isActivated = false;
		_kingBullet->_isActivated = true;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = false;

		_kingBullet->Render();
	}
	if (_itemState == ItemState::SCOPE)
	{
		_fixingTool->_isActivated = false;
			_helmet->_isActivated = false;
		  _hpPotion->_isActivated = false;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = true;
		_speedBoots->_isActivated = false;

		_scope->Render();
	}
	if (_itemState == ItemState::SPEEDBOOTS)
	{
		_fixingTool->_isActivated = false;
			_helmet->_isActivated = false;
		  _hpPotion->_isActivated = false;
		_kingBullet->_isActivated = false;
			 _scope->_isActivated = false;
		_speedBoots->_isActivated = true;

		_speedBoots->Render();
	}
}

bool RandomBox::IsCollision(Cup_Player* a)
{
	if (_itemState == ItemState::NONE)
	{
		return false;
	}

	if (_itemState == ItemState::FIXINGTOOL && _fixingTool->GetCollider()->IsCollision(a->GetCollider()))
	{
		_fixingTool->IsCollision(a);
		_isActive = false;
		return true;
	}
	if (_itemState == ItemState::HELMET && _helmet->GetCollider()->IsCollision(a->GetCollider()))
	{
		_helmet->IsCollision(a);
		_isActive = false;
		return true;
	}
	if (_itemState == ItemState::HPPOTION && _hpPotion->GetCollider()->IsCollision(a->GetCollider()))
	{
		_hpPotion->IsCollision(a);
		_isActive = false;
		return true;
	}
	if (_itemState == ItemState::KINGBULLET && _kingBullet->GetCollider()->IsCollision(a->GetCollider()))
	{
		_kingBullet->IsCollision(a);
		_isActive = false;
		return true;
	}

	if (_itemState == ItemState::SCOPE && _scope->GetCollider()->IsCollision(a->GetCollider()))
	{
		_scope->IsCollision(a);
		_isActive = false;
		return true;
	}

	if (_itemState == ItemState::SPEEDBOOTS && _speedBoots->GetCollider()->IsCollision(a->GetCollider()))
	{
		_speedBoots->IsCollision(a);
		_isActive = false;
		return true;
	}


	return false;
}
