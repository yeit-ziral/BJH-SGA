#pragma once
class ModelReader
{
	friend class ModelAnimator;
public:
	ModelReader(string name);
	~ModelReader();

	void SetShader(wstring file);

	vector<Material*> GetMaterials() { return materials; }
	vector<ModelMesh*> GetMeshes() { return meshes; }

	void Render();

	void Debug();

	bool HasBone(string boneName) { return boneMap.count(boneName) > 0; }

private:
	void ReadMaterial();
	void ReadMesh();

private:
	string name;

	vector<Material*> materials; // ��� material�� ��Ƴ��°�
	vector<ModelMesh*> meshes;

	vector<NodeData> nodes;
	vector<BoneData> bones;

	map<string, UINT> boneMap;
};