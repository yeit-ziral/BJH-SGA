#pragma once
class SRV
{
public:
	SRV(wstring file);
	~SRV();

	void Set();

private:
	// 판박이 만드는 작업 (Texture maping : Texture를 판박이 붙이듯 그려넣는것) 
	ComPtr<ID3D11ShaderResourceView> shaderResourceView;

};

