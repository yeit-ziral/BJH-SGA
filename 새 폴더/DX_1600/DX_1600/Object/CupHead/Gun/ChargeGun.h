#pragma once
class ChargeGun : public Gun
{
public:
	ChargeGun();
	virtual ~ChargeGun();

	virtual void Update();
	virtual void Render();
	void PostRender();

	void Charge();

	void Fire(Vector2 dir);

	void Selected(bool Bool) { _selected = Bool; }

	void SetChargingCount(float a) { _chargingCount = a; }

private:

	vector<shared_ptr<class ChargingBullet>> _Cbullets;

	shared_ptr<class ChargingEffect> _chargingEffect;

	bool _isCharging = false;

	float _chargingCount = 0.0f;
};