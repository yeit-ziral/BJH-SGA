#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void Set();

private:
	// �ǹ��� ����� �۾� (Texture maping : Texture�� �ǹ��� ���̵� �׷��ִ°�) 
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;

};

