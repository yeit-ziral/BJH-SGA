#pragma once
class Particle
{
public:
	Particle();
	virtual ~Particle();

	virtual void Update() {}
	virtual void Render();
	virtual void Debug() {}

	virtual void Play(Vector3 position);
	
	void Stop();

	virtual void SetVertex() = 0; // 무조건 자식에서 세팅할거라서 순수가상함수로 만듬

protected:
	Material*		material;
	VertexBuffer*	vertexBuffer;
	GeometryShader* geometryShader;

	const UINT MAX_COUNT = 1000;

	UINT drawCount = MAX_COUNT;

	bool isAdditive = false;
	bool isActive	= false;

	Vector3 position;
};