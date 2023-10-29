#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Pumpkin";

	//exporter = new ModelExporter(name);
	//
	//exporter->ExportModel();
	
	//exporter->ExportClip("Happy Idle");
	//exporter->ExportClip("Walking");
	//exporter->ExportClip("Throw");


	//reader = new ModelReader(name);
	//
	//reader->SetShader(L"NormalMapping");
	

	//bodyparts.resize(reader->GetMeshes().size());
	//
	//for (UINT i = 0; i < reader->GetMeshes().size(); i++)
	//{
	//	bodyparts[i] = new BodyPart(reader->GetMaterials(), reader->GetMeshes()[i]);
	//}


	//model = new ModelA(name);

	//model = new Model(name);
	//model->scale *= 0.01;

	//groot = new Groot();
	pumpkin = new Ghost();
}

ModelExportScene::~ModelExportScene()
{
	//delete exporter;
	//delete model;

	//delete groot;
	delete modelAnimator;
}

void ModelExportScene::Update()
{
	//for (BodyPart* part : bodyparts)
	//{
	//	part->Update();
	//}

	//model->Update();

	//groot->Update();

	pumpkin->Update();
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

	//model->Render();

	//groot->Render();

	pumpkin->Render();
}

void ModelExportScene::PostRender()
{
	//model->GetReader()->Debug();
	//model->Debug();

	//groot->Debug();

	pumpkin->Debug();
}
