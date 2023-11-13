#include "Framework.h"
#include "FrustumCullingScene.h"

FrustumCullingScene::FrustumCullingScene()
{
	for (UINT x = 0; x < SIZE; x++)
	{
		for (UINT y = 0; y < SIZE; y++)
		{
			for (UINT z = 0; z < SIZE; z++)
			{
				Sphere* sphere = new Sphere;

				sphere->translation = Vector3(100 * x, 100 * y, 100 * z);
				sphere->scale *= 20.0f;
				sphere->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
				sphere->Update();

				spheres.emplace_back(sphere);
			}
		}
	}
}

FrustumCullingScene::~FrustumCullingScene()
{
	for (Sphere* s : spheres)
		delete s;

	spheres.clear();
}

void FrustumCullingScene::Update()
{
	for (Sphere* s : spheres)
	{
		if (CAMERA->ContainSphere(s->GetGlobalPosition(), s->Radius()))
		{
			s->Update(); // 시야에 안들어와도 계속 Update되야 하는 것들이 있기 때문에 조심해야 함
		}
	}
}

void FrustumCullingScene::PreRender()
{

}

void FrustumCullingScene::Render()
{
	for (Sphere* s : spheres)
	{
		if (CAMERA->ContainSphere(s->GetGlobalPosition(), s->Radius())) // 이 조건으로 isActive 껏다 켰다 하면 됨
		{
			s->Render();
			drawCount++;
		}
	}
}

void FrustumCullingScene::PostRender()
{
	//ImGui::Text(drawCount);
}
