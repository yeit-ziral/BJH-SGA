#pragma once
class Environment : public Singleton<Environment>
{
	friend class Singleton;
private:
	Environment();
	~Environment();

	void CreateViewport();
	void CreatePerspective();

public:
	void SetEnvironment();

	void PostRender();

	Matrix GetProjMatrix() { return projMatrix; } // 수정할 것이 아니라서 값복사로 넘김

private:
	MatrixBuffer* projBuffer;
	Matrix		  projMatrix;

	LightBuffer* lightBuffer;
};

