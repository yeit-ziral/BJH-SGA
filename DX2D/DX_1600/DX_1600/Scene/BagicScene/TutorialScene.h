#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Quad> _quad1;
	shared_ptr<Transform> _transform1;

	shared_ptr<FilterBuffer> _filterBuffer;
	shared_ptr<HPBar> _hpBar;
	int _maxHp = 100;
	int _curHp = 100;
};

