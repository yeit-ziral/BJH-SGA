#pragma once
class ChargeGun : public Gun
{
public:
	ChargeGun();
	virtual ~ChargeGun();

	virtual void Update();
	virtual void Render();

	void Charge();

	void Fire();

	void Selected(bool Bool) { _selected = Bool; }

private:

	vector<shared_ptr<class ChargingBullet>> _Cbullets;

	int _chargingCount = 0;
};