#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;
private:
	//shared_ptr<Quad> _quad1;
	//shared_ptr<Quad> _quad2;
	shared_ptr<Planet> _sun;
	shared_ptr<Planet> _sunPoint;
	shared_ptr<Planet> _earth;
	shared_ptr<Planet> _earthPoint;
	shared_ptr<Planet> _moon;

	float _angle1 = 0.0f;
	float _angle2 = 0.0f;
	float _angle1_1 = 0.0f;
	float _angle2_1 = 0.0f;
};

