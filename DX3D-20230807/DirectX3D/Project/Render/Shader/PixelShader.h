#pragma once
class PixelShader : public Shader
{
	friend class Shader;
private:
	PixelShader(wstring file);
	~PixelShader();

	ID3D11PixelShader* pixelShader;

public:
	// Shader��(��) ���� ��ӵ�
	virtual void SetShader() override;
};

