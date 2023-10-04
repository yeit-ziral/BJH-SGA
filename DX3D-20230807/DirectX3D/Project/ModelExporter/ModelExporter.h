#pragma once
class ModelExporter
{
public:
	ModelExporter(string file);
	~ModelExporter();

	void ExportMaterial(); // �о����

	wstring CreateTexture(string file); //�����

private:
	string name;

	Assimp::Importer* importer;

	const aiScene* scene;

	vector<Material*> materials; // �������� �������� vector�� ����
};