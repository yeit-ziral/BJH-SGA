#include "Framework.h"
#include "Material.h"

string Material::ID = "";

Material::Material()
{
	buffer = new MaterialBuffer();

	char path[128];

	GetCurrentDirectoryA(128, path);

	projectDir = path; // GetCurrentDirectoryA�� string�� �ȵ��� ���������� �־���

	projectDir += "Texture";

	ID += ".";
}

Material::Material(wstring file)
{
	SetShader(file);

	buffer = new MaterialBuffer();

	char path[128];

	GetCurrentDirectoryA(128, path);
	//GetCurrentDirectory(128, path);

	projectDir = path;

	projectDir += "Texture/";

	ID += ".";
}

Material::~Material()
{
	delete buffer;
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

	if (specularMap)
		specularMap->PSSetShaderResources(1);

	if (normalMap)
		normalMap->PSSetShaderResources(2);

	buffer->SetPSBuffer(1);
}

void Material::SetDiffuseMap(wstring file)
{
	diffuseMap = Texture::Get(file);

	buffer->data.hasDiffuseMap = true;
}

void Material::SetSpecularMap(wstring file)
{
	specularMap = Texture::Get(file);

	buffer->data.hasSpecularMap = true;
}

void Material::SetNormalMap(wstring file)
{
	normalMap = Texture::Get(file);

	buffer->data.hasNormalMap = true;
}

void Material::PostRender()
{
	ImGui::ColorEdit4("Diffuse", (float*)&buffer->data.diffuse);
	ImGui::ColorEdit4("Specular", (float*)&buffer->data.specular);
	ImGui::ColorEdit4("Ambient", (float*)&buffer->data.ambient);

	ImGui::Checkbox("HasDiffuseMap", (bool*)&buffer->data.hasDiffuseMap);
	ImGui::Checkbox("HasSpecularMap", (bool*)&buffer->data.hasSpecularMap);
	ImGui::Checkbox("HasNormalMap", (bool*)&buffer->data.hasNormalMap);

	ImGui::SliderFloat("Shininess", &buffer->data.shininess, 1.0f, 50.0f);

	SaveDialog();
	LoadDialog();
}

void Material::SelectMap()
{

	if (ImGui::BeginChild(ID.c_str(), ImVec2(100, 85), true)) // ImGui�� Begin�� �ϸ� �� End�� ����� ��
	{
		if (ImGui::Button("DiffuseMap"))
			Dialog->OpenDialog("Diffuse", "Select Diffuse", ".png, .jpg, .tga", "Texture/");

		if (ImGui::Button("SpecularMap"))
			Dialog->OpenDialog("Specular", "Select Specular", ".png, .jpg, .tga", "Texture/");

		if (ImGui::Button("NormalMap"))
			Dialog->OpenDialog("Normal", "Select Normal", ".png, .jpg, .tga", "Texture/");

		if (Dialog->Display("Diffuse") || Dialog->Display("Specular") || Dialog->Display("Normal"))
		{
			if (Dialog->IsOk())
			{
				string path = Dialog->GetFilePathName();

				//�����θ� ����η� �ٲ���� ��

				path = path.substr(projectDir.size() + 1, path.size());

				wstring file = ToWString(path);

				// SetDiffuse�� wstring�� �޾Ƽ� path�� wstring���� ��ȯ������� ��
				if (Dialog->GetOpenedKey() == "Diffuse")
					SetDiffuseMap(file); 

				if (Dialog->GetOpenedKey() == "Specular")
					SetSpecularMap(file);

				if (Dialog->GetOpenedKey() == "Normal")
					SetNormalMap(file);
			}

			Dialog->Close();
		}

	}
		ImGui::EndChild();
}

void Material::SaveMap(wstring file)
{
	BinaryWriter data(file);

	data.WriteData(diffuseMap->GetPath());
	data.WriteData(specularMap->GetPath());
	data.WriteData(normalMap->GetPath());
}

void Material::LoadMap(wstring file)
{
	BinaryReader data(file);

	SetDiffuseMap(data.ReadWString());
	SetSpecularMap(data.ReadWString());
	SetNormalMap(data.ReadWString());
}

void Material::SaveDialog()
{
	if (ImGui::Button("Save Map"))
		Dialog->OpenDialog("SaveMap", "Save", ".materialMap", "_TextData/");

	if (Dialog->Display("SaveMap"))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();

			path = path.substr(projectDir.size() + 4, path.size());

			wstring file = ToWString(path);
			
			if (Dialog->GetOpenedKey() == "SaveMap")
				SaveMap(file);
		}

		Dialog->Close();
	}
}

void Material::LoadDialog()
{
	if (ImGui::Button("Load Map"))
	{
		Dialog->OpenDialog("LoadMap", "Load", ".materialMap", "_TextData/");
	}

	if (Dialog->Display("LoadMap"))
	{
		if (Dialog->IsOk())
		{
			string path = Dialog->GetFilePathName();

			path = path.substr(GetTextureDir().size() + 2, path.length());

			wstring file = ToWString(path);

			if(Dialog->GetOpenedKey() == "LoadMap")
				LoadMap(ToWString(path));
		}

		Dialog->Close();
	}
}
