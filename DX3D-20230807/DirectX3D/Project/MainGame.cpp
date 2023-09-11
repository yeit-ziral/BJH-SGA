#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();

	//scene = new TextureScene();
	//scene = new TutorialScene();
	//scene = new RobotScene();
	//scene = new BoxScene();
	//scene = new TerrainScene();
	//scene = new SphereScene();
	scene = new TerrainEditorScene();
}

MainGame::~MainGame()
{
	delete scene;

	Release();
}

void MainGame::Update()
{
	scene->Update();

	Time::GetInstance()->Update();
	Keyboard::GetInstance()->Update();
	Camera::GetInstance()->Update();
}

void MainGame::Render()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	scene->PreRender();

	Device::GetInstance()->Clear();

	Enviroment::GetInstance()->SetEnviroment();

	scene->Render();

	scene->PostRender();

	Camera::GetInstance()->PostRender();

	Enviroment::GetInstance()->PostRender();

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData()); // Render 뒤에만 있으면 맨 앞에 그려짐

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
			Device::GetInstance(); // 안해줘도 생성시 만들어짐
		Enviroment::GetInstance();
		  Keyboard::GetInstance();
			  Time::GetInstance();
	  StateManager::GetInstance();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);

}

void MainGame::Release()
{
	Device::Delete();
	Shader::Delete();
	Enviroment::Delete();
	StateManager::Delete();
	Camera::Delete();
	Texture::Delete();

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
