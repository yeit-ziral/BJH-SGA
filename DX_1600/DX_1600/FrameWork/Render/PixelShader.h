#pragma once
class PixelShader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	void CreateBlob(wstring file);
	void CreatePixelShader();

	void Set();

private:
	ComPtr<ID3DBlob> pixelBlob;

	// ps : 면에 해당하는 픽셀 계산식
	ComPtr<ID3D11PixelShader> pixelShader;
};

