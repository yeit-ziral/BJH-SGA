#pragma once
class EffectScene : public Scene
{
public:
	EffectScene();
	~EffectScene();

	void Update();
	void Render();

private:
	shared_ptr<Effect> _effect;
};

