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

	Matrix GetProjMatrix() { return projMatrix; } // ������ ���� �ƴ϶� ������� �ѱ�

private:
	MatrixBuffer* projBuffer;
	Matrix		  projMatrix;

	LightBuffer* lightBuffer;
};

