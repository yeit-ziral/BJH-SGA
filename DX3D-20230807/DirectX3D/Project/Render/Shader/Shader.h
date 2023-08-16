#pragma once
class Shader
{
protected:
	Shader();
	virtual ~Shader();

public:
	static class VertexShader* GetVS(wstring file);
	static class PixelShader* GetPS(wstring file);

	static void Delete();

	virtual void SetShader() = 0;

protected:
	ID3DBlob* blob;

	static unordered_map<wstring, Shader*> shader; // 자기자신의 포인터를 가지는 변수는 static으로 만들어서 무한루프를 막음(동적할당 할 경우 만들어진 주소값을 담은 변수의 주소값을 또 만들고 이것이 반복됨)


};
