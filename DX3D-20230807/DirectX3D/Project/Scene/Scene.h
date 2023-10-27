#pragma once

class Scene
{
public:
	virtual ~Scene() = default; // ��ĳ���� ���� �� �� �Ҹ��Ű�� ���ؼ� �����Լ��� ����

	virtual void Update() = 0; // ������ ������ ������ ����, = 0�� abstract ��� ����ؼ� ���� �����Լ��� ����

	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual void Initialize() {};
	virtual void Release() {};
};