#pragma once
class Machinegun : public Gun
{
public:
	Machinegun();
	virtual ~Machinegun();

	virtual void Update();
	virtual void Render();

	virtual void Fire()override;

	void Selected(bool Bool) { _selected = Bool; }

private:

};