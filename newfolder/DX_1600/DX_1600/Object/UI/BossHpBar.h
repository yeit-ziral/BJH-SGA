#pragma once
class BossHpBar
{
public:
	BossHpBar();
	~BossHpBar();

	void Update();

	void Render();

	void SetMaxHp(int value) { _maxHp = value; } // 보스 생성할 때 보스 최대체력 받아올것
	void SetCurHp(int value) { _curHp = value; } // 매 업데이트마다 보스의 현재 체력을 받아와 갱신 할 것

	shared_ptr<Collider>GetCollider() { return _collider; }

private:
	shared_ptr<class HPBar> _hpBar;

	shared_ptr<Collider> _collider;

	shared_ptr<Transform> _frameTransform;

	shared_ptr<Quad> _frameQuad;

	int _curHp = 0;
	int _maxHp = 0;
};