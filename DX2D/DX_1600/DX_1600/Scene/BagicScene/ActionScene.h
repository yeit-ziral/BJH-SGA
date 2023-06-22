#pragma once
class ActionScene : public Scene
{
public:
	ActionScene();
	virtual ~ActionScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void GetItem();

private:
	shared_ptr<class Link> _link;
	vector<shared_ptr<class Item>> _potions;
};

