#include "framework.h"
#include "StateManager.h"

StateManager* StateManager::_instance = nullptr;

StateManager::StateManager()
{
	_sampler = make_shared<SamplerState>();

	_alpha = make_shared<BlendState>();
	_alpha->Alpha();

	_additive = make_shared<BlendState>();
	_additive->Additive();

	_blendState = make_shared<BlendState>();

	D3D11_RASTERIZER_DESC desc = {}; // -> rasterizerState를 만들기 위한 설명서 기본적인 설정에서 추가 변동사항을 넣어줌(이미 기본적으로 만들어진것을 쓰고 있었음)
	desc.CullMode = D3D11_CULL_NONE; // BackFace Culling
	desc.FillMode = D3D11_FILL_SOLID; // 
	
	DEVICE->CreateRasterizerState(&desc, &rasterizerState);

	DC->RSSetState(rasterizerState);
}

StateManager::~StateManager()
{
}
