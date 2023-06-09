#include "framework.h"
#include "Cup_Player.h"
#include "Cup_Bullet.h"

using namespace tinyxml2;

Cup_Player::Cup_Player()
{
	SOUND->Add("Cup_Attack", "Resource/Sound/attack.wav");

	_col = make_shared<CircleCollider>(50);

	CreateAction(L"Resource/CupHead/player/Idle.png", "Resource/CupHead/player/Idle.xml", "IDLE", Vector2(250, 250), Action::LOOP);
	CreateAction(L"Resource/CupHead/player/Jump.png", "Resource/CupHead/player/Jump.xml", "JUMP", Vector2(100, 100), Action::LOOP);
	CreateAction(L"Resource/CupHead/player/Run.png", "Resource/CupHead/player/Run.xml", "RUN", Vector2(100, 130), Action::LOOP);
	CreateAction(L"Resource/CupHead/player/Attack.png", "Resource/CupHead/player/Attack.xml", "ATTACK", Vector2(250, 250), Action::END, std::bind(&Cup_Player::Attack, this));
	CreateAction(L"Resource/CupHead/player/Player_Hit.png", "Resource/CupHead/player/Player_Hit.xml", "Hit", Vector2(250, 250), Action::LOOP);

	_sprites[0]->SetPS(ADD_PS(L"Shader/ActionFilterPS.hlsl"));
	_intBuffer = make_shared<IntBuffer>();
	_intBuffer->_data.aInt = 0;
	_intBuffer->_data.bInt = 300;

	_transform = make_shared<Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0.0f,9.876f));

	SetAction(IDLE);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));

	_hp = 10;
}

Cup_Player::~Cup_Player()
{
}

void Cup_Player::Update()
{
	if (!_isAlive)
		return;

	Input();
	Jump();
	Hit();

	_col->Update();

	_actions[_curState]->Update();
	_intBuffer->Update();
	_sprites[_curState]->Update();
	_transform->Update();

	for (auto bullet : _bullets)
		bullet->Update();
}

void Cup_Player::Render()
{
	if (!_isAlive)
		return;

	_transform->SetBuffer(0);
	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_intBuffer->SetPSBuffer(1);
	_sprites[_curState]->Render();

	_col->Render();

	for (auto bullet : _bullets)
		bullet->Render();
}

void Cup_Player::PostRender()
{
	ImGui::SliderInt("State", (int*)&_curState, 0, 4);
	ImGui::SliderInt("isMosaic", &_intBuffer->_data.aInt, 0, 1);
	ImGui::SliderInt("Mosaic Magnitude", &_intBuffer->_data.bInt, 0, 300);
}

void Cup_Player::CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type, CallBack event)
{
	shared_ptr<SRV> srv = ADD_SRV(srvpath);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	string path = xmlpath;
	document->LoadFile(path.c_str());

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

	_actions.push_back(action);
	_sprites.push_back(sprite);
}

void Cup_Player::Input()
{
	if (KEY_DOWN(VK_LBUTTON) && _isAttack == false && _isJump == false)
	{
		SOUND->Play("Cup_Attack", 0.3f);
		_isAttack = true;
		SetAction(ATTACK);

		if (MOUSE_POS.x > _col->GetTransform()->GetWorldPosition().x)
			SetRight();
		if (MOUSE_POS.x < _col->GetTransform()->GetWorldPosition().x)
			SetLeft();
	}

	if (KEY_PRESS('A'))
	{
		Move(LEFT_VECTOR);
		SetLeft();
	}
	if (KEY_UP('A'))
	{
		SetLeft();
	}

	if (KEY_PRESS('D'))
	{
		Move(RIGHT_VECTOR);
		SetRight();
	}
	if (KEY_UP('D'))
	{
		SetRight();
	}

	if (KEY_DOWN(VK_SPACE) && _isJump == false)
	{
		//CAMERA->ShakeStart(8.0f, 5.0f);
		_jumpPower = 800.0f;
		_isJump = true;
	}

	if (_curState != RUN && _curState != IDLE)
		return;

	if (KEY_PRESS('A') || KEY_PRESS('D'))
		SetAction(RUN);
	else if (_curState == RUN)
		SetAction(IDLE);
}

void Cup_Player::Jump()
{
	if (_isJump == true)
		SetAction(JUMP);
	else if (_curState == JUMP && _isJump == false)
		SetAction(IDLE);

	// �߷�����
	{
		_jumpPower -= 15;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_col->GetTransform()->AddVector2(Vector2(0, 1) * _jumpPower * DELTA_TIME);
	}
}

void Cup_Player::Attack()
{
	Vector2 dir = MOUSE_POS - _col->GetPos();

	_isAttack = false;
	SetAction(IDLE);

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Cup_Bullet> obj)-> bool { return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	(*bulletIter)->Shoot(Vector2(dir.x, 0.0f), _col->GetTransform()->GetWorldPosition());
}

bool Cup_Player::IsCollision_Bullets(shared_ptr<Collider> col)
{
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

void Cup_Player::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Cup_Player::Hit()
{
	if (_isHit == true)
	{
		SetAction(HIT);
		_isHit = false;
	}
	else if (_curState == HIT && _isHit == false)
		SetAction(IDLE);
}

void Cup_Player::SetLeft()
{
	for (auto sprite : _sprites)
		sprite->SetLeft();
}

void Cup_Player::SetRight()
{
	for (auto sprite : _sprites)
		sprite->SetRight();
}
