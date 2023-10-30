#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singletion;
public:
	StateManager();
	~StateManager();

	void CreateSamplerState();
	void CreateRasterizerState();
	void CreateBlendState();

public:
	RasterizerState* GetRS() { return rasterizerState; }

	void AlphaBegin();
	void AlphaEnd();

private:
	SamplerState* samplerState = nullptr;
	RasterizerState* rasterizerState = nullptr;

	vector<BlendState*> blendStates;
};