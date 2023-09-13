#include "framework.h"
#include "Cup_Monster.h"
#include "../Gun/Bullets/Cup_Bullet.h"
using namespace tinyxml2;

Cup_Monster::Cup_Monster()
{
	_monster = make_shared<CircleCollider>(100);

	CreateAction(L"Resource/CupHead/boss/BossStart.png", "Resource/CupHead/boss/BossStart.xml", "START", Vector2(100, 100), Action::Type::END, std::bind(&Cup_Monster::StartEvent, this));
	CreateAction(L"Resource/CupHead/boss/BossLoop.png", "Resource/CupHead/boss/BossLoop.xml", "LOOP", Vector2(200, 200), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/boss/BossDie.png", "Resource/CupHead/boss/BossDie.xml", "DEAD", Vector2(300, 300), Action::Type::END, std::bind(&Cup_Monster::DieEvent, this));

	// Action Event 설정
	{
		_actions[State::START]->SetAlmostEndEvent([this]()->void { _state = State::LOOP; });
		_actions[2]->SetEndEvent(std::bind(&Cup_Monster::DieEvent, this));
	}

	_intBuffer = make_shared<IntBuffer>();
	_intBuffer->_data.aInt = 1;
	_intBuffer->_data.bInt = 300;

	_transform = make_shared<Transform>();
	_transform->SetParent(_monster->GetTransform());

	_bowSlot = make_shared<Transform>();
	_bowSlot->SetParent(_transform);

	_bow = make_shared<Quad>(L"Resource/CupHead/weapon/Bow.png");
	_bowTrans = make_shared<Transform>();

	_bowTrans->SetParent(_bowSlot);
	_bowTrans->SetPosition({ 50,0 });
	_bowTrans->SetAngle(-PI * 0.75f);

	_sprites[END]->SetPS(ADD_PS(L"Shader/ActionFilterPS.hlsl"));

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}

}

Cup_Monster::~Cup_Monster()
{
}

void Cup_Monster::Update(Vector2 targetPos)
{
	if (!_isAlive)
		return;

	if (_hp <= 0)
		_isAlive = false;

	// 중력적용
	{
		_jumpPower -= 1000.0f * DELTA_TIME;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_monster->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
	}


	if (_state == State::END && _intBuffer->_data.bInt > 1)
		_intBuffer->_data.bInt -= 5;

	_monster->Update();

	_actions[_state]->Update();
	_intBuffer->Update();

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Update();
	_transform->Update();

	SetBowAngle(targetPos);
	_bowSlot->SetPosition(_transform->GetPos());
	_bowSlot->Update();
	_bowTrans->Update();

	for (auto& bullet : _bullets)
		bullet->Update();
}

void Cup_Monster::Render()
{
	if (!_isAlive)
		return;

	_transform->SetBuffer(0);

	_intBuffer->SetPSBuffer(1);

	_sprites[_state]->Render();

	_monster->Render();

	_bowTrans->SetBuffer(0);
	_bow->Render();

	for (auto& bullet : _bullets)
		bullet->Render();
}

void Cup_Monster::PostRender()
{
	ImGui::Text("Hp : %d", _hp);
}

void Cup_Monster::Attack(Vector2 targetPos)
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

void Cup_Monster::CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvpath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

	document->LoadFile(xmlpath.c_str());

	XMLElement* textureAtlas = document->FirstChildElement();
	XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;


	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, actionName, type);
	action->Play();
	action->SetEndEvent(event);
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvpath, size);

	action->Update();
	sprite->Update();

	sprite->SetCurClip(action->GetCurClip());

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Monster::GetAttacked(int amount)
{
	if (!_isAlive)
		return;
	_hp -= amount;


	if (_hp <= 0)
	{
		_hp = 0;
		
		EFFECT_PLAY("Exp", _monster->GetTransform()->GetWorldPosition());

		DieEvent();
	}
}

bool Cup_Monster::IsCollsion_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetBulletCollider()))
		{
			bullet->_isActive = false;
			return true;
		}
	}

	return false;
}

void Cup_Monster::Roaming()
{
}

void Cup_Monster::SetBowAngle(Vector2 targetPos)
{
	Vector2 monsterToPlayer = targetPos - _monster->GetTransform()->GetPos();
	float angle = monsterToPlayer.Angle();
	_bowSlot->SetAngle(angle);
}

void Cup_Monster::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Monster::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}
