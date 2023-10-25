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
	//scene = new TerrainEditorScene();
	//scene = new ModelExportScene();
	//scene = new ModelAnimationScene();
	scene = new CollisionScene();

	FONT->Add("D2Coding", L"D2Coding");
}

MainGame::~MainGame()
{
	delete scene;

	Release();

	FONT->Delete();
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

	if (isWireFrame)
	{
		RS->ChangeState(D3D11_FILL_WIREFRAME);
	}
	else
	{
		RS->ChangeState(D3D11_FILL_SOLID);
	}

	scene->PreRender();

	Device::GetInstance()->Clear();

	Environment::GetInstance()->SetEnvironment();

	scene->Render();
	Time::GetInstance()->Render();

	scene->PostRender();

	Camera::GetInstance()->Debug();

	Environment::GetInstance()->PostRender();

	ImGui::Checkbox("WireFrame", &isWireFrame);

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData()); // Render �ڿ��� ������ �� �տ� �׷���

	Device::GetInstance()->Present();
}

void MainGame::Initialize()
{
			Device::GetInstance(); // �����൵ ������ �������
	   Environment::GetInstance();
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
	Environment::Delete();
	StateManager::Delete();
	Camera::Delete();
	Texture::Delete();

	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
