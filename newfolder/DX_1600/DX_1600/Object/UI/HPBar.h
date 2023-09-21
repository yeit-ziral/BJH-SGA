#pragma once

class HPBar
{
public:
	HPBar(wstring path = L"Resource/UI/RedSquare.png", Vector2 size = Vector2(800, 50));
	~HPBar();

	void Update();
	void PostRender();

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }
	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }

	void SetMaxHp(UINT value)
	{
		_maxHP = value;
		_intBuffer->_data.aInt = (int)value;
	}
	void SetCurHp(UINT value)
	{
		_curHP = value;
		_intBuffer->_data.bInt = (int)value;
	}

	Vector2 GetXSizeHalf() { return _quad->GetQuadHalfSize(); }

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	shared_ptr<IntBuffer> _intBuffer;
	UINT _maxHP = 100;
	UINT _curHP = 100;
};
