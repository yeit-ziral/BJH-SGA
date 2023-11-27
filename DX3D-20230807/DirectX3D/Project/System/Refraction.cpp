#include "Framework.h"
#include "Refraction.h"

UINT Refraction::index = 0;

Refraction::Refraction(wstring file)
{
	buffer = new WaterBuffer();

	normalMap = Texture::Get(file);

	renderTarget = new RenderTarget(2048, 2048);
	depthStencil = new DepthStencil(2048, 2048);

	// Debug

	quad = new Quad(Vector2(200, 200));
	quad->translation = { 100, 100, 0 };

	Texture* texture = Texture::Get(L"Refraction_" + to_wstring(index++), renderTarget->GetSRV());

	quad->GetMaterial()->SetDiffuseMap(texture);
	quad->Update();
}

Refraction::~Refraction()
{
	delete buffer;
	delete renderTarget;
	delete depthStencil;
	delete quad;
}

void Refraction::Update()
{
	buffer->data.waveTime += Time::Delta();
}

void Refraction::SetPreRender()
{
	renderTarget->Set(depthStencil);
}

void Refraction::SetRender()
{
	buffer->SetPSBuffer(10);

	DC->PSSetShaderResources(11, 1, &renderTarget->GetSRVRef());
	normalMap->PSSetShaderResources(12);
}

void Refraction::PostRender()
{
	quad->Render();
}

void Refraction::Debug()
{
	ImGui::Text("Water Option");
	ImGui::ColorEdit4("WaterColor", (float*)&buffer->data.color);

	ImGui::SliderFloat("WaterSpeed"		, (float*)&buffer->data.waveSpeed	, 0.0f, 1.0f);
	ImGui::SliderFloat("WaterScale"		, (float*)&buffer->data.waveScale	, 0.0f, 1.0f);
	ImGui::SliderFloat("WaterShininess"	, (float*)&buffer->data.waveShiniess, 1.0f,50.0f);
	ImGui::SliderFloat("WaterFresnel"	, (float*)&buffer->data.fresnel		, 0.0f, 1.0f);
}
