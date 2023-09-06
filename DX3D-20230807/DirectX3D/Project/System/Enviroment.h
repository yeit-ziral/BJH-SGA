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

private:
	MatrixBuffer* projBuffer;

	LightBuffer* lightBuffer;

};

