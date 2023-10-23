#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Dwarven_Axe";

	exporter = new ModelExporter(name);
	
	exporter->ExportModel();
	
	//exporter->ExportClip("Happy Idle");
	//exporter->ExportClip("Walking");
	//exporter->ExportClip("Throw");


	reader = new ModelReader(name);
	
	reader->SetShader(L"NormalMapping");
	//
	//bodyparts.resize(reader->GetMeshes().size());
	//
	//for (UINT i = 0; i < reader->GetMeshes().size(); i++)
	//{
	//	bodyparts[i] = new BodyPart(reader->GetMaterials(), reader->GetMeshes()[i]);
	//}


	//model = new ModelA(name);

	model = new Model(name);

	//groot = new Groot();
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
	delete model;

	//delete groot;
	delete modelAnimator;
}

void ModelExportScene::Update()
{
	//for (BodyPart* part : bodyparts)
	//{
	//	part->Update();
	//}

	model->Update();

	//groot->Update();
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

	//groot->Render();
}

void ModelExportScene::PostRender()
{
	model->GetReader()->Debug();

	//groot->Debug();
}
