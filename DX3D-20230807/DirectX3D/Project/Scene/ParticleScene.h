#pragma once
class ParticleScene : public Scene
{
public:
	ParticleScene();
	~ParticleScene();

	virtual void Update()		override;
	virtual void PreRender()	override;
	virtual void Render()		override;
	virtual void PostRender()	override;

private:
	Particle* particle;

	Collider* collider;
};
