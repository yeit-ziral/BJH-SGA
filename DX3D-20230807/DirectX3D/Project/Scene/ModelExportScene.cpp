#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";

	exporter = new ModelExporter(name);

	exporter->ExportModel();

	exporter->ExportClip("Hip Hop Dancing");

	//reader = new ModelReader(name);
	//
	//reader->SetShader(L"NormalMapping");
	//
	//bodyparts.resize(reader->GetMeshes().size());
	//
	//for (UINT i = 0; i < reader->GetMeshes().size(); i++)
	//{
	//	bodyparts[i] = new BodyPart(reader->GetMaterials(), reader->GetMeshes()[i]);
	//}


	//model = new ModelA(name);

	//model = new Model(name);

	modelAnimator = new ModelAnimator(name);
	modelAnimator->ReadClip("Hip Hop Dancing");
	modelAnimator->CreateTexture();
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
	//delete model;

	delete modelAnimator;
}

void ModelExportScene::Update()
{
	//for (BodyPart* part : bodyparts)
	//{
	//	part->Update();
	//}

	//model->Update();

	modelAnimator->Update();
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

	modelAnimator->Render();
}

void ModelExportScene::PostRender()
{
	//model->GetReader()->Debug();
}
