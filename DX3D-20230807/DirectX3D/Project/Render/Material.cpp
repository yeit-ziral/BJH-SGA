#include "Framework.h"
#include "Material.h"

Material::Material()
{
}

Material::Material(wstring file)
{
	SetShader(file);
}

Material::~Material()
{
}

void Material::SetVertexShader(wstring file)
{
	vertexShader = Shader::GetVS(file);
}

void Material::SetPixelShader(wstring file)
{
	pixelShader = Shader::GetPS(file);
}

void Material::SetShader(wstring file)
{
	SetVertexShader(file);
	SetPixelShader(file);
}

void Material::SetMaterial()
{
	vertexShader->SetShader();
	pixelShader->SetShader();

	if (diffuseMap) // diffuseMap �Ⱦ��� �͵��� ������ ���� ���� diffuseMap�� nullptr�� �ƴѰ͸� ����ϵ��� ��
		diffuseMap->PSSetShaderResources(0);
}

void Material::SetDiffuseMap(wstring file)
{
	diffuseMap = Texture::Get(file);
}