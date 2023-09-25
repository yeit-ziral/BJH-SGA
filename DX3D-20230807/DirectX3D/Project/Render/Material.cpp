#include "Framework.h"
#include "Material.h"

int Material::ID = 0;

Material::Material()
{
	buffer = new MaterialBuffer();

	SetShader(L"TerrainBrush");

	SetDiffuseMap(L"LandScape/Fieldstone_DM.tga");
	SetSpecularMap(L"LandScape/fieldstone_SM.tga");
	SetNormalMap(L"LandScape/fieldstone_NM.tga");


	char path[128];

	GetCurrentDirectoryA(128, path);

	projectDir = path; // GetCurrentDirectoryA�� string�� �ȵ��� ���������� �־���

	projectDir += "Texture";

	char pathC[128];

	//GetCurrentDirectoryA(128, pathC);

	//projectDirMap = pathC;

	//projectDirMap += "_TextData/";

	ID += 1; // Key�� �ߺ� �ȵǰ� �Ϸ���

	label = "Material" + to_string(ID);
}

Material::Material(wstring file)
{
	buffer = new MaterialBuffer();

	SetDiffuseMap(L"LandScape/Fieldstone_DM.tga");
	SetSpecularMap(L"LandScape/fieldstone_SM.tga");
	SetNormalMap(L"LandScape/fieldstone_NM.tga");

	SetShader(file);

	char path[128];

	GetCurrentDirectoryA(128, path);

	projectDir = path;

	projectDir += "Texture/";

	char pathC[128];

	GetCurrentDirectoryA(128, pathC);

	projectDirMap = pathC;

	projectDirMap += "_TextData/";

	ID += 1;

	label = "Material" + to_string(ID);
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
		ImGui::InputText("Label", (char*)label.data(), 128);

	if (ImGui::BeginMenu(label.c_str(), true))
	{

		ImGui::ColorEdit4((label + "Diffuse").c_str(), (float*)&buffer->data.diffuse);
		ImGui::ColorEdit4((label + "Specular").c_str(), (float*)&buffer->data.specular);
		ImGui::ColorEdit4((label + "Ambient").c_str(), (float*)&buffer->data.ambient);

		ImGui::Checkbox((label + "HasDiffuseMap").c_str(), (bool*)&buffer->data.hasDiffuseMap);
		ImGui::Checkbox((label + "HasSpecularMap").c_str(), (bool*)&buffer->data.hasSpecularMap);
		ImGui::Checkbox((label + "HasNormalMap").c_str(), (bool*)&buffer->data.hasNormalMap);

		ImGui::SliderFloat((label + "Shininess").c_str(), &buffer->data.shininess, 1.0f, 50.0f);

		if (ImGui::Button(("Save " + label).c_str()))
			Save(ToWString(label + " Data"));

		if (ImGui::Button(("Load " + label).c_str()))
			Load(ToWString(label + " Load"));

		ImGui::EndMenu();
	}

	SelectMap();

	//SaveDialogMap();
	//LoadDialogMap();
}

void Material::SelectMap()
{

	if (ImGui::BeginMenu(label.c_str())) // ImGui�� Begin�� �ϸ� �� End�� ����� ��
	{
		if (ImGui::Button("DiffuseMap"))
			Dialog->OpenDialog("Diffuse", "Select Diffuse", ".png, .jpg, .tga", "Texture/");

		if (ImGui::Button("NormalMap"))
			Dialog->OpenDialog("Normal", "Select Normal", ".png, .jpg, .tga", "Texture/");

		if (ImGui::Button("SpecularMap"))
			Dialog->OpenDialog("Specular", "Select Specular", ".png, .jpg, .tga", "Texture/");

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

		ImGui::EndMenu();
	}
}

//void Material::SaveMap(wstring file)
//{
//	BinaryWriter data(file);
//
//	data.WriteData(diffuseMap->GetPath());
//	data.WriteData(specularMap->GetPath());
//	data.WriteData(normalMap->GetPath());
//}
//
//void Material::LoadMap(wstring file)
//{
//	BinaryReader data(file);
//
//	SetDiffuseMap(data.ReadWString());
//	SetSpecularMap(data.ReadWString());
//	SetNormalMap(data.ReadWString());
//}
//
//void Material::SaveDialogMap()
//{
//	if (ImGui::Button("Save Map"))
//		Dialog->OpenDialog("SaveMap", "Save", ".materialMap", "_TextData/");
//
//	if (Dialog->Display("SaveMap"))
//	{
//		if (Dialog->IsOk())
//		{
//			string path = Dialog->GetFilePathName();
//
//			path = path.substr(projectDirMap.size() + 1, path.size());
//
//			wstring file = ToWString(path);
//			
//			if (Dialog->GetOpenedKey() == "SaveMap")
//				SaveMap(file);
//		}
//
//		Dialog->Close();
//	}
//}
//
//void Material::LoadDialogMap()
//{
//	if (ImGui::Button("Load Map"))
//	{
//		Dialog->OpenDialog("LoadMap", "Load", ".materialMap", "_TextData/");
//	}
//
//	if (Dialog->Display("LoadMap"))
//	{
//		if (Dialog->IsOk())
//		{
//			string path = Dialog->GetFilePathName();
//
//			path = path.substr(projectDirMap.size() + 1, path.length());
//
//			wstring file = ToWString(path);
//
//			if(Dialog->GetOpenedKey() == "LoadMap")
//				LoadMap(ToWString(path));
//		}
//
//		Dialog->Close();
//	}
//}

void Material::Save(wstring file)
{
	BinaryWriter data(file);

	data.WriteData(label);

	if (vertexShader)
		data.WriteData(vertexShader->GetPath());
	else
		data.WriteData(L"");

	if (pixelShader)
		data.WriteData(pixelShader->GetPath());
	else
		data.WriteData(L"");

	if (diffuseMap)
		data.WriteData(diffuseMap->GetPath());
	else
		data.WriteData(L"");

	if (specularMap)
		data.WriteData(specularMap->GetPath());
	else
		data.WriteData(L"");

	if (normalMap)
		data.WriteData(normalMap->GetPath());
	else
		data.WriteData(L"");
}

void Material::Load(wstring file)
{
	BinaryReader data(file);

	if (!data.Succeeded())
		return;

	label = data.ReadString();

	wstring str;

	str = data.ReadWString();
	if (str != L"")
		vertexShader = Shader::GetVS(str);


	str = data.ReadWString();
	if (str != L"")
		pixelShader = Shader::GetPS(str);


	str = data.ReadWString();
	if (str != L"")
		diffuseMap = Texture::Get(str);


	str = data.ReadWString();
	if (str != L"")
		specularMap = Texture::Get(str);

	str = data.ReadWString();
	if (str != L"")
		normalMap = Texture::Get(str);
}
