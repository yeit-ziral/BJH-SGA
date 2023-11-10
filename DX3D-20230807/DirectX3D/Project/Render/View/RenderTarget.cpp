#include "Framework.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget(UINT width, UINT height)
	: width(width), height(height)
{
	CreateRTVTexture();
	CreateRTV();
	CreateSRV();
}

RenderTarget::~RenderTarget()
{
	rtvTexture->Release();
	rtv->Release();
	srv->Release();
}

void RenderTarget::Set(DepthStencil* depthStencil, Vector4 clearColor)
{
	DC->OMSetRenderTargets(1, &rtv, depthStencil->GetDSV());

	DC->ClearRenderTargetView(rtv, (float*)&clearColor);
	depthStencil->Clear();

	Environment::GetInstance()->SetEnvironment();
	Environment::GetInstance()->SetViewport(width, height);
}

void RenderTarget::SetMulti(RenderTarget** targets, UINT count, DepthStencil* depthStencil, Vector4 clearColor)
{
	vector<ID3D11RenderTargetView*> rtvs;

	for (UINT i = 0; i < count; i++)
	{
		rtvs.push_back(targets[i]->GetRTV());
		DC->ClearRenderTargetView(rtvs.back(), (float*)&clearColor);
	}

	depthStencil->Clear();

	DC->OMSetRenderTargets(count, rtvs.data(), depthStencil->GetDSV());
	Environment::GetInstance()->SetEnvironment();
}

void RenderTarget::CreateRTVTexture()
{
	D3D11_TEXTURE2D_DESC desc;

	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1; // Ȯ�� ��ҿ� ���� ����
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	DEVICE->CreateTexture2D(&desc, nullptr, &rtvTexture);
}

void RenderTarget::CreateRTV()
{
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};

	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	DEVICE->CreateRenderTargetView(rtvTexture, &rtvDesc, &rtv);
}

void RenderTarget::CreateSRV()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2DArray.MipLevels = 1;

	DEVICE->CreateShaderResourceView(rtvTexture, &srvDesc, &srv);
}
