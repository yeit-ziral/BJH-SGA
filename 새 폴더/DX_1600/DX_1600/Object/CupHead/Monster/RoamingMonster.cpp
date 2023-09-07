#include "framework.h"
#include "RoamingMonster.h"
#include "../Gun/Bullets/Cup_Bullet.h"
using namespace tinyxml2;

RoamingMonster::RoamingMonster()
{
	_monster = make_shared<CircleCollider>(150);

	_monsterQuad = make_shared<Quad>(L"Resource/Player.png");

	_transform = make_shared<Transform>();
	_transform->SetParent(_monster->GetTransform());

	_bowSlot = make_shared<Transform>();
	_bowSlot->SetParent(_transform);

	_bow = make_shared<Quad>(L"Resource/CupHead/weapon/Bow.png");
	_bowTrans = make_shared<Transform>();

	_bowTrans->SetParent(_bowSlot);
	_bowTrans->SetPosition({ 50,0 });
	_bowTrans->SetAngle(-PI * 0.75f);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));
}

RoamingMonster::~RoamingMonster()
{
}

void RoamingMonster::Update(Vector2 targetPos)
{
	if (!_isAlive)
		return;

	if (_hp <= 0)
		_isAlive = false;

	_monster->Update();

	_transform->Update();

	SetBowAngle(targetPos);
	_bowSlot->SetPosition(_transform->GetPos());
	_bowSlot->Update();
	_bowTrans->Update();

	for (auto& bullet : _bullets)
		bullet->Update();
}

void RoamingMonster::Render()
{
	if (!_isAlive)
		return;

	_monster->Render();

	_transform->SetBuffer(0);

	_monsterQuad->Render();

	_bowTrans->SetBuffer(1);
	_bow->Render();

	for (auto& bullet : _bullets)
		bullet->Render();
}

void RoamingMonster::PostRender()
{
	ImGui::SliderInt("RoamingMonsterState", (int*)&_state, 0, 3);
	ImGui::Text("R-monsterPos : %f, %f", _monster->GetPos().x, _monster->GetPos().y);
	ImGui::Text("bowTransPos : %f , %f", _bowSlot->GetPos().x, _bowSlot->GetPos().y);
}

void RoamingMonster::Attack(Vector2 targetPos)
{
	_time += DELTA_TIME;
	if (_time > _atkSpeed)
	{
		_time = 0.0f;
	}
	else
		return;

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Cup_Bullet>& obj)-> bool {return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	//_atkCool = true;
	Vector2 startPos = _bowTrans->GetWorldPosition();
	Vector2 dir = targetPos - startPos;
	dir.Normallize();
	(*bulletIter)->SetAngle(dir.Angle());
	(*bulletIter)->Shoot(dir, startPos);
}

void RoamingMonster::GetAttacked(int amount)
{
	if (!_isAlive)
		return;

	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0;

		DieEvent();
	}
}

bool RoamingMonster::IsCollsion_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetBulletCollider()))
		{
			EFFECT_PLAY("Hit", bullet->GetPosition());
			bullet->_isActive = false;
			return true;
		}
	}

	return false;
}

void RoamingMonster::Roaming()
{
}

void RoamingMonster::SetBowAngle(Vector2 targetPos)
{
	Vector2 monsterToPlayer = targetPos - _monster->GetTransform()->GetPos();

	float angle = monsterToPlayer.Angle();
	_bowSlot->SetAngle(angle);
}

void RoamingMonster::SetLeft()
{
	_monsterQuad->FlipVertically();
}

void RoamingMonster::SetRight()
{
}
