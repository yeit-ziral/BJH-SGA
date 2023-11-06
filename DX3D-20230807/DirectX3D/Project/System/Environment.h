#pragma once
class Environment : public Singleton<Environment>
{
	friend class Singleton;
private:
	Environment();
	~Environment();

	void CreateViewport();
	void CreatePerspective();
	void CreateOrthographic();

	void DebugLight(int lightIndex);

public:
	void SetEnvironment();

	void PostSet();

	void PostRender();

	Matrix GetProjMatrix() { return persMatrix; } // 수정할 것이 아니라서 값복사로 넘김

private:
	MatrixBuffer* persBuffer;
	Matrix		  persMatrix;

	MatrixBuffer* orthoBuffer;
	Matrix		  orthoMatrix;

	ViewBuffer* UIViewBuffer;

	LightBuffer* lightBuffer;
};

