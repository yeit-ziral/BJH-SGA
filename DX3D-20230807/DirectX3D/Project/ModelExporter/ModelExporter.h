#pragma once
class ModelExporter
{
public:
	ModelExporter(string file);
	~ModelExporter();

	void ExportMaterial(string name);

	void ReadMaterial(); //읽어오기

	wstring CreateTexture(string file); //만들기

private:
	string name;

	Assimp::Importer* importer;

	const aiScene* scene;

	vector<Material*> materials; // 부위별로 뜯어오려고 vector로 만듬
};