#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singletion;
public:
	StateManager();
	~StateManager();

	void CreateSamplerState();

private:
	SamplerState* samplerState = nullptr;
};