#pragma once
class GoombaScene : public Scene
{
public:
	GoombaScene();
	virtual ~GoombaScene();

	virtual void Updata() override;
	virtual void Render() override;

private:
};

