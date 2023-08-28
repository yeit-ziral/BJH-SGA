#pragma once
class TextureScene : public Scene
{
public: 
	TextureScene();
	~TextureScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

	Quad* quad;
	Quad* quad2;
	//Quad* quad3;
	//Quad* quad4;
};

