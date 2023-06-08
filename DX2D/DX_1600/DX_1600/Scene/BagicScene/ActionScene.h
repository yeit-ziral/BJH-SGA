#pragma once
class ActionScene : public Scene
{
public:
	ActionScene();
	virtual ~ActionScene();

	virtual void Update() override;
	void Collider_Update();
	virtual void Render() override;
	virtual void PostRender() override;

	void GetItem();

private:
	shared_ptr<class Link> _link;
	shared_ptr<class Item> _potion;
};

