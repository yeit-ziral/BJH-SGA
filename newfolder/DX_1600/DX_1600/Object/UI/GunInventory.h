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

	void FillInventory();

	void DropGun();

private:
	vector<class GunInvenCell> _invencells;
};