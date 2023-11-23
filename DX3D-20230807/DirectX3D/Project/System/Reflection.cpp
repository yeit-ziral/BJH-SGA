#include "Framework.h"
#include "Reflection.h"

UINT Reflection::index = 0;

Reflection::Reflection(Transform* target)
	:target(target)
{
	renderTarget = new RenderTarget(1280, 720);
	depthStencil = new DepthStencil(1280, 720);

	camera = new Camera();

	// Debug

	quad = new Quad(Vector2(200, 200));
	quad->translation = { 100, 100, 0 };

	Texture* texture = Texture::Get(L"Reflection" + to_wstring(index++), renderTarget->GetSRV());

	quad->GetMaterial()->SetDiffuseMap(texture);
	quad->Update();
}

Reflection::~Reflection()
{
	delete renderTarget;
	delete depthStencil;
	delete camera;
	delete quad;
}

void Reflection::Update()
{
	Vector3 pos = CAMERA->translation;
	Vector3 rot = CAMERA->rotation;

	pos.y = target->GetGlobalPosition().y * 2.0f - pos.y;
	rot.x *= -1.0f;

	camera->translation = pos;

	camera->rotation = rot;

	camera->Update();
}

void Reflection::SetPreRender()
{
	renderTarget->Set(depthStencil);

	camera->SetView(); // Slot 1 �ߺ�
}

void Reflection::SetRender()
{
	camera->GetViewBuffer()->SetVSBuffer(10); // �Ϲ����� ī�޶�� ���� �޾���
	DC->PSSetShaderResources(10, 1, &renderTarget->GetSRVRef()); 
	// GetSRV()�� ID3D11ShaderResourceView* GetSRV()�� ������ Lvalue(���� ������ ��)�� �ƴ� -> ���� ������ �Ұ����ϱ� ���� ������ ID3D11ShaderResourceView*& GetSRVRef()�� �ٲ㼭  Refference ���� �ذ�
}

void Reflection::PostRender()
{
	quad->Render();
}
