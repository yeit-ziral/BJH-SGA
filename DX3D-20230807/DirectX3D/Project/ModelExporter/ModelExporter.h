#pragma once
class ModelExporter
{
public:
	ModelExporter(string file);
	~ModelExporter();

	void ExportModel();

private:
	void ExportMaterial(); // 읽어오기
	void ExportMesh(); // 읽어오기

	wstring CreateTexture(string file); //만들기

	void ReadMesh(aiNode* node);
	void WriteMesh();

private:
	string name;

	Assimp::Importer* importer;

	const aiScene* scene;

	vector<MeshData*> meshes; // 부위별로 뜯어오려고 vector로 만듬

	vector<string> materialNames;
};