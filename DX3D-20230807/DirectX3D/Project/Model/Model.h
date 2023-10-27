#pragma once
class Model : public Transform
{
public:
	Model(string name, wstring shaderFile = L"NormalMapping");
	~Model();

	void Update();
	void Render();

	void Debug();

	ModelReader* GetReader() { return reader; }

private:
	ModelReader* reader;
};

