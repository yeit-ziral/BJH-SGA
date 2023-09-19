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

	// 아이템을 먹을 때 Items를 바꿔주는 함수
	void SetItemState(GunState itemState) { _gunState = itemState; }

	bool _isFilled = false;

	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }

	shared_ptr<Gun>GetNowGun();

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	GunState _gunState = GunState::NONE;

	shared_ptr<class NormalGun>	 _normalGun;
	shared_ptr<class Machinegun> _machineGun;
	shared_ptr<class ChargeGun>  _chargeGun;
};