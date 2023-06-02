#pragma once
class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Collider_Update() {}
	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PostRender() {}

private:
};
