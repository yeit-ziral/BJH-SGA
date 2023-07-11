#pragma once
class ChargeGun : public Gun
{
public:
	ChargeGun();
	virtual ~ChargeGun();

	virtual void Update();
	virtual void Render();

	virtual void Fire()override;

	void Selected(bool Bool) { _selected = Bool; }

private:
};