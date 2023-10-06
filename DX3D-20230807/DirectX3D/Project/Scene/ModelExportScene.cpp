#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";

	exporter = new ModelExporter(name);

	exporter->ExportModel();

	reader = new ModelReader("Knight D Pelegrini");
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
}

void ModelExportScene::Update()
{
	for (ModelMesh* mesh : reader->GetMeshes())
	{
		mesh->GetVertices();
	}
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	reader->SetShader(L"NormalMapping");
}

void ModelExportScene::PostRender()
{
}
