#pragma once
class ModelReader
{
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

	vector<Material*> GetMaterials() { return materials; }
	vector<ModelMesh*> GetMeshes() { return meshes; }

	void Render();

	void Debug();

private:
	void ReadMaterial();
	void ReadMesh();

private:
	string name;

	vector<Material*> materials; // 모든 material을 모아놓는곳
	vector<ModelMesh*> meshes;
};