#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	scene = new TutorialScene();
}

MainGame::~MainGame()
{
	delete scene;

	Release();
}

void MainGame::Update()
{
	scene->Update();
}

void MainGame::Render()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	scene->PreRender();

	Device::GetInstance()->Clear();

	scene->Render();

	scene->PostRender();

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData()); // Render �ڿ��� ������ �� �տ� �׷���

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

	Device::GetInstance(); // �����൵ ������ �������
	Enviroment::GetInstance();
}

void MainGame::Release()
{
	Device::Delete();
	Shader::Delete();
	Enviroment::Delete();

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}