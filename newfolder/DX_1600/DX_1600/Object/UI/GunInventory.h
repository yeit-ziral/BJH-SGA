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
	
	// 필드에서 먹으면 각 총의 _inInventory를 true로 바꿈
	// 먹으면 여기에서 먹은 순서대로 쌓임

	void Update();

	void Render();

	void FillInventory();

	void DropGun();

private:
	vector<class GunInvenCell> _invencells;
};