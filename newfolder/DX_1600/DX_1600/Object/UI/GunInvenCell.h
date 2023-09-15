#pragma once
class GunInvenCell
{
	enum class GunState
	{
		NONE,
		NORMAL,
		MACHINE,
		CHARGE
	};
public:
	GunInvenCell();
	~GunInvenCell();

	void Update();

	void PostRender();

	GunState GetGunState() { return _gunState; }

	bool _isFilled = false;

	void FillInven();

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	GunState _gunState = GunState::NONE;

	shared_ptr<class NormalGun>	 _normalGun;
	shared_ptr<class Machinegun> _machineGun;
	shared_ptr<class ChargeGun>  _chargeGun;
};