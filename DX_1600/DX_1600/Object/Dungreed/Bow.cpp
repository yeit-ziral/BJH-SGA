#include "framework.h"
#include "Bow.h"

Bow::Bow(wstring file, Vector2 scale)
{
	_bow = make_shared<Quad>(file);
	_bow->GetTransform()->SetScale(scale);
	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Bullets> bullet = make_shared<Bullets>();
		_bullets.push_back(bullet);
	}
}

Bow::~Bow()
{
}

void Bow::Fire()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x0001)
	{
		Vector2 temp = mousePos - _bow->GetTransform()->GetWorldPosition();
		
		auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(), [](const shared_ptr<Bullets> obj)->bool
		{
			return !obj->IsActive();
		});

		if (bulletIter == _bullets.end())
			return;

		(*bulletIter)->Shoot(dir, _bow->GetTransform()->GetWorldPosition());
	}
}

void Bow::Update()
{
	_bow->Update();
	for (auto bullet : _bullets)
		bullet->Update();
	
}

void Bow::Render()
{
}
