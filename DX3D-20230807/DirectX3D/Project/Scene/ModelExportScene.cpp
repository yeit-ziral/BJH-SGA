#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Y Bot";

	//exporter = new ModelExporter(name);

	//exporter->ExportModel();

	//bodyparts.resize(3);

	//for (UINT i = 0; i < 3; i++)
	//{
	//	bodyparts[i] = new BodyPart(reader->GetMaterials(), reader->GetMeshes()[i]);
	//}


	//model = new ModelA(name);

	model = new Model(name);
}

ModelExportScene::~ModelExportScene()
{
	//delete exporter;
}

void ModelExportScene::Update()
{
	//for (BodyPart* part : bodyparts)
	//{
	//	part->Update();
	//}

	model->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	//for (int i = 0; i < reader->GetMeshes().size(); i++)
	//{
	//	bodyparts[i]->Render(i);
	//}

	model->Render();
}

void ModelExportScene::PostRender()
{
	model->GetReader()->Debug();
}
