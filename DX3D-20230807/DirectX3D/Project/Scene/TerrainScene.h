#pragma once
class TerrainScene : public Scene
{
public:
	TerrainScene();
	~TerrainScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	Terrain* terrain;

	//// ·Îº¿
	//Cube* _body;
	//Cube* _head;
	//Cube* _leftArm;
	//Cube* _rightArm;
	//Cube* _leftLeg;
	//Cube* _rightLeg;

	Sphere* sphere;
};