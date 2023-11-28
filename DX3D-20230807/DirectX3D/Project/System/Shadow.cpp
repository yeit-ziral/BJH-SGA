#include "Framework.h"
#include "Shadow.h"

Shadow::Shadow(UINT width, UINT height)
	:width(width), height(height)
{
	renderTarget = new RenderTarget(width, height);
	depthStencil = new DepthStencil(width, height);

	viewBuffer = new   ViewBuffer();
	projBuffer = new MatrixBuffer();

	quad = new Quad(Vector2(200, 200));
	quad->translation = { 100, 100, 0 };

	Texture* texture = Texture::Get(L"DepthMap", renderTarget->GetSRV());
	quad->GetMaterial()->SetDiffuseMap(texture);
	quad->Update();
}

Shadow::~Shadow()
{
	delete renderTarget;
	delete depthStencil;
	delete viewBuffer;
	delete projBuffer;
	delete quad; 
}

void Shadow::SetPreRender()
{
	renderTarget->Set(depthStencil);
	SetViewProjection();
}

void Shadow::SetRender()
{
	viewBuffer->SetVSBuffer(11);
	projBuffer->SetVSBuffer(12);

	DC->PSSetShaderResources(10, 1, &renderTarget->GetSRVRef());
}

void Shadow::PostRender()
{
	quad->Render();
}

void Shadow::SetViewProjection()
{
	LightBuffer::LightData& lightData = Environment::GetInstance()->GetLightBuffer()->data.lights[0];  // ������ �������ϰ�� �� ���� �÷��� �� ������ 0���� ���� ���

	Matrix view = XMMatrixLookAtLH(lightData.position, Vector3(), Vector3(0, 1, 0));

	Matrix proj = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.1f, 5000.0f);

	viewBuffer->SetData(view, XMMatrixInverse(nullptr, view));
	projBuffer->SetData(proj);

	viewBuffer->SetVSBuffer(1);
	projBuffer->SetVSBuffer(2);
}
