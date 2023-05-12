#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void Set(int slot = 0);

	Vector2 GetImageSize() { return _size; }

private:
	// �ǹ��� ����� �۾� (Texture maping : Texture�� �ǹ��� ���̵� �׷��ִ°�) 
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;

	Vector2 _size;
};

