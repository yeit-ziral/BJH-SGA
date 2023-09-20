#include "framework.h"
#include "Cup_Boss.h"
#include "../Gun/Bullets/Cup_Bullet.h"
#include "../Gun/Bullets/HowitzerBullet.h"
#include "../../UI/HPBar.h"

using namespace tinyxml2;

Cup_Boss::Cup_Boss()
{
	_collider = make_shared<RectCollider>(Vector2(Vector2(200, 150)));
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());

	_transform->SetPosition(Vector2(20, 30));
	_intBuffer = make_shared<IntBuffer>();
	_intBuffer->_data.aInt = 3;
	_intBuffer->_data.bInt = 300;

	CreateAction(L"Resource/CupHead/boss/Clown_Intro_1.png", "Resource/CupHead/boss/Clown_Intro_1.xml", "START", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Intro_2.png", "Resource/CupHead/boss/Clown_Intro_2.xml", "LOOP", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEventDash, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Move_1.png", "Resource/CupHead/boss/Clown_Move_1.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Move_2.png", "Resource/CupHead/boss/Clown_Move_2.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Move_3.png", "Resource/CupHead/boss/Clown_Move_3.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Ready_Dash.png", "Resource/CupHead/boss/Clown_Ready_Dash.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Dash.png", "Resource/CupHead/boss/Clown_Dash.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Dash_Loop.png", "Resource/CupHead/boss/Clown_Dash_Loop.xml", "END", Vector2(600, 400), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/boss/Clown_Wall_Crash.png", "Resource/CupHead/boss/Clown_Wall_Crash.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEventCrash, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Intro_1.png", "Resource/CupHead/boss/Clown_Intro_1.xml", "HOWITZER1", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Intro_2.png", "Resource/CupHead/boss/Clown_Intro_2.xml", "HOWITZER2", Vector2(600, 400), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/boss/Clown_Intro_1.png", "Resource/CupHead/boss/Clown_Intro_1.xml", "SHOOT1", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::EndEvent, this));
	CreateAction(L"Resource/CupHead/boss/Clown_Intro_2.png", "Resource/CupHead/boss/Clown_Intro_2.xml", "SHOOT2", Vector2(600, 400), Action::Type::LOOP);
	CreateAction(L"Resource/CupHead/boss/Clown_Die_Middle.png", "Resource/CupHead/boss/Clown_Die_Middle.xml", "END", Vector2(600, 400), Action::Type::END, std::bind(&Cup_Boss::DieEvent, this));


	SetRight();

	//action Event 설정
	{
		_actions[Boss_State::START]->SetAlmostEndEvent(std::bind(&Cup_Boss::EndEvent, this));
	}

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}
	for (int i = 0; i < 3; i++)
	{
		shared_ptr<HowitzerBullet> bullet = make_shared<HowitzerBullet>();
		_Hbullets.push_back(bullet);
	}

	_hpBar = make_shared<HPBar>(L"Resource/UI/RedSquare.png", Vector2(800, 50));
	_hpBar->SetPosition(Vector2(WIN_WIDTH * 0.5f, 10.0f));
}

Cup_Boss::~Cup_Boss()
{
}

void Cup_Boss::Update(Vector2 target)
{
	if (_isAlive == false)
		return;

	_collider->Update();
	_intBuffer->Update();
	_actions[_state]->Update();

	_sprites[_state]->Update();

	_transform->Update();

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());

	Attack(target);

	//if (_isWallCrash == true)
	//{
	//	_state = Boss_State::DASHSTOP;
	//	_actions[_state]->Play();
	//	_actions[DASHLOOP]->Reset();
	//	_isWallCrash = false;
	//}

	// AtteckPattern에 따라 한번씩 공격

	if (_hp <= 0)
	{
		_state = DIE;
		_sprites[_state]->SetPS(ADD_PS(L"Shader/ActionFilterPS.hlsl"));

		if (_intBuffer->_data.bInt <= 1)
			_intBuffer->_data.bInt = 100;
		_intBuffer->_data.bInt -= 1;
	}

	// 보스 중력적용
	{
		_jumpPower -= 800.0f * DELTA_TIME;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_collider->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
	}

	for (auto bullet : _Hbullets)
		bullet->Update();

	for (auto bullet : _bullets)
		bullet->Update();

}

void Cup_Boss::Render()
{
	if (_isAlive == false)
		return;
	_transform->SetBuffer(0);
	_intBuffer->SetPSBuffer(1);


	_sprites[_state]->Render();

	_collider->Render();

	for (auto bullet : _Hbullets)
		bullet->Render();

	for (auto bullet : _bullets)
		bullet->Render();
}

void Cup_Boss::PostRender()
{
	ImGui::Text("BossHP : %d", _hp);
	ImGui::SliderInt("State", (int*)&_state, 0, 13);
	//ImGui::SliderInt("Mosaic", &_intBuffer->_data.bInt, 0, 300);
	for (auto bullet : _Hbullets)
		bullet->PostRender();
}

void Cup_Boss::CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvPath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

	document->LoadFile(xmmlPath.c_str());

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
	shared_ptr<Sprite> sprite = make_shared<Sprite>(srvPath, size);

	action->Update();
	sprite->Update();

	_actions.push_back(action);
	_sprites.push_back(sprite);
}


void Cup_Boss::Attack(Vector2 target)
{
	if (_attackState == Boss_Attack::DASH)
	{
		Dash();
		if (_isWallCrash == true)
		{
			if (_isLeft == true)
			{
				SetLeft();
			}
			else
			{
				SetRight();
			}
			_state = Boss_State::DASHSTOP;
			_actions[_state]->Play();
			_actions[DASHLOOP]->Reset();
			_isWallCrash = false;
			_attackState = Boss_Attack::HOWITZER;
		}
	}

	if (_attackState == Boss_Attack::HOWITZER && _state == Boss_State::HOWITZER2)
	{
		Howitzer(target);
		// 발사가 다 끝나면 _state를 SHOOT1으로 바꿔줌

		if (shootCount == 3 && waitTime > 2.0f)
		{
			_attackState = Boss_Attack::SHOOT;
			shootCount = 0;
			waitTime = 0.0f;

			_state = Boss_State::SHOOT1;
			_actions[_state]->Play();
			_actions[HOWITZER2]->Reset();
		}

	}

	if (_attackState == Boss_Attack::SHOOT && _state == Boss_State::SHOOT2)
	{
		Shoot(target);
		// 벽에 도달하면 _state를 READY1으로 바꿔줌
		if (_isWallCrash == true)
		{
			if (_isLeft == true)
			{
				SetLeft();
			}
			else
			{
				SetRight();
			}
			_state = Boss_State::READY1;
			_attackState = Boss_Attack::DASH;
			_actions[_state]->Play();
			_actions[SHOOT2]->Reset();
			_isWallCrash = false;
		}
	}

	waitTime += 1 * DELTA_TIME;
}

void Cup_Boss::Dash()
{
	if (_state == Boss_State::DASHSTART || _state == Boss_State::DASHLOOP)
	{
		if (_isLeft == true)
		{
			Vector2 movePos = Vector2(-500.0f, 0.0f);
			Move(movePos);
		}
		else
		{
			Vector2 movePos = Vector2(500.0f, 0.0f);
			Move(movePos);
		}
	}
}

void Cup_Boss::Howitzer(Vector2 target)
{
	if (_atkCool)
	{
		_timer += DELTA_TIME;
		if (_timer > _coolingtimeH)
		{
			_timer = 0.0f;
			_atkCool = false;
		}
		return;
	}
	// 곡사포 발사 3번, 3초 기다림
	auto bulletIter = std::find_if(_Hbullets.begin(), _Hbullets.end(),
		[](shared_ptr<HowitzerBullet>& obj)-> bool { return !obj->_isActive; });

	if (bulletIter == _Hbullets.end())
		return;

	(*bulletIter)->Shoot(target, this->GetCollider()->GetTransform()->GetWorldPosition());

	shootCount += 1;

	_atkCool = true;
}

void Cup_Boss::Shoot(Vector2 target)
{
	if (_isLeft == true)
	{
		Vector2 movePos = Vector2(-50.0f, 0.0f);
		Move(movePos);
	}
	else
	{
		Vector2 movePos = Vector2(50.0f, 0.0f);
		Move(movePos);
	}

	if (_atkCool)
	{
		_timer += DELTA_TIME;
		if (_timer > _coolingtime)
		{
			_timer = 0.0f;
			_atkCool = false;
		}
		return;
	}

	//총알 발사 애니메이션과 총알 발사
	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](shared_ptr<Cup_Bullet>& obj)-> bool { return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	// 타겟의 위치를 받아 발사 방향 정함
	Vector2 dir = target - _collider->GetTransform()->GetWorldPosition();

	(*bulletIter)->Shoot(dir, _transform->GetWorldPosition());

	_atkCool = true;
}

void Cup_Boss::EndEventDash()
{
	if (_coolDown > 0)
	{
		_actions[LOOP]->Reset();
		_state = Boss_State::LOOP;
		_actions[_state]->Play();
		_coolDown -= 1;
		return;
	}
	if (_coolDown <= 0)
	{
		_state = Boss_State::READY1;
		_actions[_state]->Play();
		_coolDown -= RandomNum(10, 14);
		return;
	}
}

void Cup_Boss::EndEvent()
{
	if (_state == Boss_State::START)
	{
		_state = Boss_State::LOOP;
		_actions[_state]->Play();
		_actions[START]->Reset();
		return;
	}

	if (_state == Boss_State::READY1)
	{
		_state = Boss_State::READY2;
		_actions[_state]->Play();
		_actions[READY1]->Reset();
		return;
	}

	if (_state == Boss_State::READY2)
	{
		_state = Boss_State::READY3;
		_actions[_state]->Play();
		_actions[READY2]->Reset();
		return;
	}


	if (_state == Boss_State::READY3)
	{
		_state = Boss_State::DASHREADY;
		_actions[_state]->Play();
		_actions[READY3]->Reset();
		return;
	}

	if (_state == Boss_State::DASHREADY)
	{
		_state = Boss_State::DASHSTART;
		_actions[_state]->Play();
		_actions[DASHREADY]->Reset();
		return;
	}

	if (_state == Boss_State::DASHSTART)
	{
		_state = Boss_State::DASHLOOP;
		_actions[_state]->Play();
		_actions[DASHSTART]->Reset();
		return;
	}

	if (_state == Boss_State::HOWITZER1)
	{
		_state = Boss_State::HOWITZER2;
		_actions[_state]->Play();
		_actions[HOWITZER1]->Reset();
		return;
	}

	if (_state == Boss_State::SHOOT1)
	{
		_state = Boss_State::SHOOT2;
		_actions[_state]->Play();
		_actions[SHOOT1]->Reset();
		return;
	}
}

void Cup_Boss::DieEvent()
{
	_isAlive = false;
	_state = Boss_State::START;
}

void Cup_Boss::EndEventCrash()
{
	
	_state = Boss_State::HOWITZER1;
	_actions[_state]->Play();
	_actions[DASHSTOP]->Reset();
	return;
}

void Cup_Boss::GetAttacked(int amount)
{
	if (!_isAlive)
		return;
	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0;

		EFFECT_PLAY("Exp2", _collider->GetTransform()->GetWorldPosition());

		DieEvent();
	}
}

bool Cup_Boss::IsCollsion_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _Hbullets)
	{
		if (bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetBulletCollider()))
		{
			bullet->_isActive = false;
			EFFECT_PLAY("Exp2", bullet->GetBulletCollider()->GetTransform()->GetWorldPosition());
			return true;
		}
	}

	for (auto bullet : _bullets)
	{
		if (bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetBulletCollider()))
		{
			bullet->_isActive = false;
			EFFECT_PLAY("Hit", bullet->GetPosition());
			return true;
		}
	}

	return false;
}

void Cup_Boss::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
	_isLeft = false;
}

void Cup_Boss::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
	_isLeft = true;
}