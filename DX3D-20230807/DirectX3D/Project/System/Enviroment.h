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

	Matrix GetProjMatrix() { return projMatrix; } // 수정할 것이 아니라서 값복사로 넘김

private:
	MatrixBuffer* projBuffer;
	Matrix		  projMatrix;

	LightBuffer* lightBuffer;
};

