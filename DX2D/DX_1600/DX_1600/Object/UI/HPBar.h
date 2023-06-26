#pragma once
class HPBar
{
public:
	HPBar(wstring path, Vector2 size);
	~HPBar();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	void SetMaxHP(UINT value) { _maxHP = value; _intBuffer->_data.aInt = (int)value; }
	void SetCurHP(UINT value) { _curHP = value; _intBuffer->_data.bInt = (int)value; }

private:
	shared_ptr<Transform> _transform;
	shared_ptr<Quad> _quad;

	shared_ptr<IntBuffer> _intBuffer;

	UINT _maxHP = 100;
	UINT _curHP = 100;
};

