#pragma once
class Enviroment : public Singleton<Enviroment>
{
	friend class Singleton;
private:
	Enviroment();
	~Enviroment();

	void CreateViewport();
	void CreatePerspective();

public:
	void SetEnviroment();

	void PostRender();

	Matrix GetProjMatrix() { return projMatrix; } // ������ ���� �ƴ϶� ������� �ѱ�

private:
	MatrixBuffer* projBuffer;
	Matrix		  projMatrix;

	LightBuffer* lightBuffer;
};

