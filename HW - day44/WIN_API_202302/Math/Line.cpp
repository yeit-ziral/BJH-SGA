#include "framework.h"
#include "Line.h"

Line::Line(Vector2 start, Vector2 end)
	: _start(start)
	, _end(end)
{
	HPEN green = CreatePen(PS_SOLID, 3, GREEN);
	_pens.push_back(green);
	HPEN red = CreatePen(PS_SOLID, 3, RED);
	_pens.push_back(red);
}

Line::~Line()
{
	for (auto* pen : _pens)
	{
		DeleteObject(pen);
	}
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curPen]);

	MoveToEx(hdc, _start.x, _start.y, nullptr);
	LineTo(hdc, _end.x, _end.y);
}

ColResult_Line Line::IsCollision(shared_ptr<Line> other)
{
	ColResult_Line result;
	result.isCollision = false;
	result.contact = Vector2(0, 0);

	Vector2 a = this->GetVector2();

	Vector2 a1 = other->_start - this->_start;
	Vector2 a2 = other->_end - this->_start;

	Vector2 b = other->GetVector2();

	Vector2 b1 = this->_start - other->_start;
	Vector2 b2 = this->_end - other->_start;

	if (a.IsBetween(a1, a2) && b.IsBetween(b1, b2))
	{
		result.isCollision = true;
		
		//충돌지점 넣기
		/*float aLean = a.y / a.x ;
		float bLean = b.y / b.x ;

		float Px = ((-(aLean * this->_start.x) + this->_start.y) - (-(bLean * other->_start.x) + other->_start.y)) / (bLean - aLean);
		float Py = bLean * (Px - other->_start.x) + other->_start.y;
		result.contact.x = Px;
		result.contact.y = Py;*/

		float aArea = abs(a.Cross(a1));
		float bArea = abs(a.Cross(a2));

		float ratio = aArea / (aArea + bArea);

		float length = b.Length() * ratio;

		Vector2 bNormal = b.NormalVector2();

		result.contact = other->_start + bNormal * length;

		return result;
	}
	result.contact = { -100000.0f, -100000.0f };
	return result;
}

bool Line::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector2 a = other->GetCenter() - this->_start;
	Vector2 b = this->GetVector2();
	Vector2 c = other->GetCenter() - this->_end;

	float sToC = b.Cross(a) / b.Length();

	if (sToC < other->GetRadius())
	{
		if (c.Length() > other->GetRadius() || a.Length() > other->GetRadius())
			return true;
	}

	return false;
	
}
