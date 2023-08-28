#pragma once
class GunInventory
{
public:
	enum Gun
	{
		NORMAL,
		MACHINE,
		CHARGE
	};

	GunInventory();
	~GunInventory();
	
	// �ʵ忡�� ������ �� ���� _inInventory�� true�� �ٲ�
	// ������ ���⿡�� ���� ������� ����

	void Update();

	void Render();

private:
	shared_ptr<class NormalGun> _normalGun;
	shared_ptr<class Machinegun> _machineGun;
	shared_ptr<class ChargeGun> _chargeGun;
};