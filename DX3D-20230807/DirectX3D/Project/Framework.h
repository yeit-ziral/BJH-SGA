﻿#pragma once

#include "__Others/targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <functional>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>

using namespace std;
using namespace DirectX;

// lib 형태로 만드는 이유는 기본적으로 외부종속성에 포함되어있지 않기 때문이다
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#pragma comment(lib, "ImGui.lib")

#include "ImGuiFileDialog.h"

#include "DirectXTex.h"
#include "DirectXTex.inl"

#pragma comment(lib, "DirectXTex.lib")

#define WIN_WIDTH 1280.0f
#define WIN_HEIGHT 720.0f

#define DEVICE Device::GetInstance()->GetDevice()
#define DC	   Device::GetInstance()->GetDC()

#define KEY_UP(p)		Keyboard::GetInstance()->Up(p)
#define KEY_DOWN(p)		Keyboard::GetInstance()->Down(p)
#define KEY_PRESS(p)	Keyboard::GetInstance()->Press(p)

#define CAMERA Camera::GetInstance()->GetTransform()

#define RS StateManager::GetInstance()->GetRS()

#define PI 3.141592


typedef XMMATRIX Matrix; // typedef(typedefine)은 코드라서 ; 필요, define은 메크로라서 ; 없음
typedef XMFLOAT4 Vector4;
typedef XMFLOAT2 Vector2;

#include "Utility/Singleton.h"

#include "Utility/Vector3.h"

#include "Utility/Keyboard.h"
#include "Utility/Time.h"
#include "Utility/Utility.h"

using namespace Utility;

#include "Object/Transform.h"

#include "System/Device.h"

#include "Render/Shader/Shader.h"
#include "Render/Shader/VertexShader.h"
#include "Render/Shader/PixelShader.h"



#include "Render/Buffer/VertexLayout.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Buffer/IndexBuffer.h"
#include "Render/Buffer/ConstBuffer.h"
#include "Render/Buffer/GlobalBuffer.h"

#include "Render/Texture/Texture.h"
#include "Render/Mesh.h"
#include "Render/Material.h"

#include "Render/State/RasterizerState.h"
#include "Render/State/SamplerState.h"
#include "Render/State/StateManager.h"

#include "System/Environment.h"
#include "System/Camera.h"

#include "Object/Basic/Cube.h"
#include "Object/Basic/Quad.h"
#include "Object/Basic/Box.h"
#include "Object/Basic/Box2.h"
#include "Object/Basic/TextureCube.h"
#include "Object/Basic/Circle.h"
#include "Object/Basic/Sphere.h"

#include "Object/Landscape/Terrain.h"
#include "Object/Landscape/TerrainEditor.h"

#include "Scene/Scene.h"
#include "Scene/TutorialScene.h"
#include "Scene/TextureScene.h"
#include "Scene/RobotScene.h"
#include "Scene/BoxScene.h"
#include "Scene/TerrainScene.h"
#include "Scene/SphereScene.h"
#include "Scene/TerrainEditorScene.h"

#include "MainGame.h"

extern HWND hWnd; // extern : 변수의 전방선언 같은 느낌

extern Vector3 mousePos;