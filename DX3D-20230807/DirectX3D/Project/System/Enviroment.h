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

private:
	MatrixBuffer* projBuffer;
};

