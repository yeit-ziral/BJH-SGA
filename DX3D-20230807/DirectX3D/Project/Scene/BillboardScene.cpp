#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
	terrain = new Terrain(L"Landscape/Dirt2.png", L"HeightMap/HeightMap.png");

	//for (UINT i = 0; i < 1000; i++)
	//{
	//	Vector2 size;

	//	size.x = Random(3.0f, 10.0f);
	//	size.y = Random(3.0f, 10.0f);

	//	Quad* tree = new Quad(size);
	//	tree->GetMaterial()->SetDiffuseMap(L"Landscape/Tree.png");

	//	Vector3 pos;

	//	pos.x = Random(0.0f, terrain->GetSize().x);
	//	pos.z = Random(0.0f, terrain->GetSize().y);

	//	pos.y = terrain->GetHeight(pos) + size.y * 0.5f;

	//	tree->translation = pos;

	//	trees.emplace_back(tree);
	//}

	material = new Material();
	material->SetShader(L"13Billboard");
	material->SetDiffuseMap(L"Landscape/Tree.png");

	geometryShader = Shader::GetGS(L"13Billboard");

	//vertices.resize(COUNT);

	for (UINT i = 0; i < COUNT; i++)
	{
		Vector2 size;

		size.x = Random(3.0f, 10.0f);
		size.y = Random(3.0f, 10.0f);
	
		Vector3 pos;
	
		pos.x = Random(0.0f, terrain->GetSize().x);
		pos.z = Random(0.0f, terrain->GetSize().y);
	
		pos.y = terrain->GetHeight(pos) + size.y * 0.5f;

		VertexTexture vertex;
		vertex.pos = pos;
		vertex.uv = size;

		vertices.push_back(vertex);
	}

	vertexBuffer = new VertexBuffer(vertices);

	drawVertices.resize(COUNT);
}

BillboardScene::~BillboardScene()
{
	delete terrain;

	//for (Quad* tree : trees)
	//	delete tree;

	//trees.clear();

	delete material;
	delete vertexBuffer;
}

void BillboardScene::Update()
{
	//for (Quad* tree : trees)
	//{
	//	//tree->rotation = CAMERA->rotation;
	//	//tree->rotation.x = 0.0f;

	//	Vector3 dir = tree->GetGlobalPosition() - CAMERA->GetGlobalPosition();

	//	float angle = atan2f(dir.x, dir.z); // 바라보는 방향

	//	tree->rotation.y = angle;

	//	tree->Update();
	//}

	//drawCount = 0;

	//for (UINT i = 0; i < COUNT; i++)
	//{
	//	if (CAMERA->ContainPoint(vertices[i].pos))
	//	{
	//		drawVertices[drawCount++] = vertices[i];
	//	}
	//}

	//vertexBuffer->UpdateVertex(drawVertices.data(), drawCount);

	terrain->Update();
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
	terrain->Render();

	StateManager::GetInstance()->AlphaToCoverageEnable();
	//StateManager::GetInstance()->DepthWriteMaskZero();

	//for (Quad* tree : trees)
	//	tree->Render();

	vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

		  material->SetMaterial();
	geometryShader->SetShader(); // terrain에도 적용되서 terrain이 안그려짐

	DC->Draw(drawCount, 0);

	DC->GSSetShader(nullptr, nullptr, 0);

	StateManager::GetInstance()->AlphaEnd();
	//StateManager::GetInstance()->DepthEnable();
}

void BillboardScene::PostRender()
{
	terrain->GetMaterial()->Debug();
}
