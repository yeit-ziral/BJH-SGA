#include "framework.h"
#include "Bow.h"

Bow::Bow(wstring file, Vector2 scale)
{
	_bow = make_shared<Quad>(L"Resource/Bow.png");

}

Bow::~Bow()
{
}

void Bow::Shoot()
{
}

void Bow::Update()
{
}

void Bow::Render()
{
}
