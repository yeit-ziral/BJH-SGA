#pragma once
class PixelShader : public Shader
{
public:
	PixelShader(wstring file);
	~PixelShader();

private:
	ID3D11PixelShader* pixelShader;

	// Shader을(를) 통해 상속됨
	virtual void SetShader() override;
};

