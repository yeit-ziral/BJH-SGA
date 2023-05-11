#pragma once
class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void Set(int slot = 0);

private:
	// 판박이 붙혀주는 사람
	ComPtr<ID3D11SamplerState> samplerState;
};

