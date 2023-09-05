#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singletion;
public:
	StateManager();
	~StateManager();

	void CreateSamplerState();
	void CreateRasterizerState();

	RasterizerState* GetRS() { return rasterizerState; }

private:
	SamplerState* samplerState = nullptr;
	RasterizerState* rasterizerState = nullptr;
};