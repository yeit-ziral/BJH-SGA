#pragma once
class PixelShader : public Shader
{
public:
	PixelShader(wstring file);
	~PixelShader();

private:
	ID3D11PixelShader* pixelShader;

	// Shader��(��) ���� ��ӵ�
	virtual void SetShader() override;
};

