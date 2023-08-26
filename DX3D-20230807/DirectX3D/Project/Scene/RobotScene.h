#pragma once
class RobotScene : public Scene
{
public:
	RobotScene();
	~RobotScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	Cube* _body;
	Cube* _head;
	Cube* _leftArm;
	Cube* _rightArm;
	Cube* _leftLeg;
	Cube* _rightLeg;
};
