#pragma once
class ModelReader
{
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

	vector<ModelMesh*> GetMeshes() { return meshes; }

private:
	void ReadMaterial();
	void ReadMesh();

private:
	string name;

	vector<Material*> materials; // ��� material�� ��Ƴ��°�
	vector<ModelMesh*> meshes;
};