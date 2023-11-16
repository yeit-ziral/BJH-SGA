#pragma once
class Sprite : public Particle
{
public:
	Sprite(wstring file, Vector2 size, float frameX, float frameY, bool isAdditive = false, float maxFrameCount = 0);
	~Sprite();
	
	
	//override 안붙여도 기능적으론 정상작동 함 -> 함수이름을 잘못 썼을 때, 에러가 뜨지 않아 알아채기 어렵다

	virtual void Update() override;
	virtual void Render() override;
	virtual void Debug()  override;

	void Play(Vector3 position) override;

private:
	virtual void SetVertex() override;

private:
	FloatValueBuffer* buffer;

	vector<VertexTexture> vertex;

	float time = 0.0f;
	float speed = 1.0f;

	UINT curFrameCount = 0;
	UINT maxFrameCount = 0;

	Vector2 size;

};