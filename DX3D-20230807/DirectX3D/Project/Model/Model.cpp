#include "Framework.h"
#include "Model.h"

Model::Model(string name, wstring shaderFile)
{
	reader = new ModelReader(name);
	reader->SetShader(shaderFile);
}

Model::~Model()
{

}

void Model::Update()
{
	Transform::Update();
}

void Model::Render()
{
	Transform::SetWorld();

	reader->Render();
}
