#pragma once
class BossHpBar
{
public:
	BossHpBar();
	~BossHpBar();

	void Update();

	void Render();

	void SetMaxHp(int value) { _maxHp = value; } // ���� ������ �� ���� �ִ�ü�� �޾ƿð�
	void SetCurHp(int value) { _curHp = value; } // �� ������Ʈ���� ������ ���� ü���� �޾ƿ� ���� �� ��

	shared_ptr<Collider>GetCollider() { return _collider; }

private:
	shared_ptr<class HPBar> _hpBar;

	shared_ptr<Collider> _collider;

	shared_ptr<Transform> _frameTransform;

	shared_ptr<Quad> _frameQuad;

	int _curHp = 0;
	int _maxHp = 0;
};