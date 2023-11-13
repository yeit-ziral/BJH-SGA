#pragma once

class Camera;

class Environment : public Singleton<Environment>
{
	friend class Singleton;
private:
	Environment();
	~Environment();

	void CreatePerspective();
	void CreateOrthographic();

	void DebugLight(int lightIndex);

public:
	void SetViewport(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);

	void SetEnvironment();

	void PostSet();

	void PostRender();

	Matrix GetProjMatrix() { return persMatrix; } // ������ ���� �ƴ϶� ������� �ѱ�

	MatrixBuffer* GetPerspectiveBuffer() { return persBuffer; }

	Camera* GetMainCamera() { return mainCamera; }

private:
	MatrixBuffer* persBuffer;
	Matrix		  persMatrix;

	MatrixBuffer* orthoBuffer;
	Matrix		  orthoMatrix;

	ViewBuffer* UIViewBuffer;

	LightBuffer* lightBuffer;

	Camera* mainCamera;
};

