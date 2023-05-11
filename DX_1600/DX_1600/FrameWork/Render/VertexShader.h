#pragma once
class VertexShader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void CreateBlob(wstring file);
	void CreateInputLayout();
	void CreateVertexShader();

	void Set();

private:
	ComPtr<ID3DBlob> vertexBlob; // VertexShader ���� �� �ʿ��� ��

	// vs : �� ������ �����Ǵ� ����... World View Projection (WVP)
	ComPtr<ID3D11VertexShader> vertexShader;

	// inputLayout : ������ ��ġ
	ComPtr<ID3D11InputLayout> inputLayout;
};

