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
	ComPtr<ID3DBlob> vertexBlob; // VertexShader 만들 때 필요한 얘

	// vs : 각 정점에 대응되는 계산식... World View Projection (WVP)
	ComPtr<ID3D11VertexShader> vertexShader;

	// inputLayout : 정보의 배치
	ComPtr<ID3D11InputLayout> inputLayout;
};

