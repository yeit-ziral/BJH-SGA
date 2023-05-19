#include "framework.h"
#include "Bow.h"

Bow::Bow(wstring file, Vector2 scale)
{
	_bow = make_shared<Quad>(L"Resource/Bow.png");
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
		auto iter = std::find_if(_bullets.begin(), _bullets.end(),
			[](const shared_ptr<Bullets>& bullet)-> bool
			{
				if (bullet->IsActive() == false)
					return true;
				return false;
			});

		Vector2 temp = mousePos - _bow->GetTransform()->GetWorldPosition();
		if (iter != _bullets.end())
		{
			(*iter)->Shoot(temp.NormalVector2(), _bow->GetTransform()->GetWorldPosition(), 0.1f, temp.Angle());
		}
	}
}

void Bow::Update()
{
}

void Bow::Render()
{
}
