#pragma once
class ModelExporter
{
public:
	ModelExporter(string file);
	~ModelExporter();

	void ExportModel();

private:
	void ExportMaterial(); // �о����
	void ExportMesh(); // �о����

	wstring CreateTexture(string file); //�����

	void ReadMesh(aiNode* node);
	void WriteMesh();

private:
	string name;

	Assimp::Importer* importer;

	const aiScene* scene;

	vector<MeshData*> meshes; // �������� �������� vector�� ����

	vector<string> materialNames;
};