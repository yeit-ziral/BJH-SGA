#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Knight D Pelegrini";

	//exporter = new ModelExporter(name);
	//
	//exporter->ExportModel();
	//
	//exporter->ExportClip("Hip Hop Dancing");
	//exporter->ExportClip("Breathing Idle");
	//exporter->ExportClip("Running");


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
	modelAnimator->ReadClip("Breathing Idle");
	modelAnimator->ReadClip("Running");
	modelAnimator->CreateTexture();
}

ModelExportScene::~ModelExportScene()
{
	//delete exporter;
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

	if (KEY_DOWN('1'))
		modelAnimator->PlayClip(0, speed, takeTime);

	if (KEY_DOWN('2'))
		modelAnimator->PlayClip(1, speed, takeTime);

	if (KEY_DOWN('3'))
		modelAnimator->PlayClip(2, speed, takeTime);
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

	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);
}
